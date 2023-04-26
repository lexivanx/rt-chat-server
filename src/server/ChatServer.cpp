#include "ChatServer.h"
#include "SocketWrapper.h"

#include <iostream>
#include <thread>
#include <fstream>

void ChatServer::loadIoTDeviceConfig(std::string& host, unsigned short& port) {
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cerr << "Error opening configuration file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        size_t delimiterPos = line.find("=");
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            if (key == "iot_device_host") {
                host = value;
            } else if (key == "iot_device_port") {
                port = static_cast<unsigned short>(std::stoi(value));
            }
        }
    }

    configFile.close();
}

ChatServer::ChatServer(unsigned short port) : m_port(port), m_iotComm() {
    std::string iotDeviceHost;
    unsigned short iotDevicePort;
    loadIoTDeviceConfig(iotDeviceHost, iotDevicePort);
    m_iotComm.setHostAndPort(iotDeviceHost, iotDevicePort);
}

ChatServer::~ChatServer() {}

void ChatServer::handleClient(SocketWrapper clientSocket) {
    while (true) {
        std::string message;
        if (clientSocket.receive(message, 1024) <= 0) {
            break;
        }

        // Check if the received message is an IoT command
        if (message.substr(0, 4) == "iot:") {
            std::string iotCommand = message.substr(4);
            handleIoTCommand(iotCommand);
        } else {
            // Regular chat message handling
            std::cout << "Message from client " << clientSocket.getPeerAddress() << ": " << message << std::endl;
        }
    }

    clientSocket.close();
    std::cout << "Client disconnected: " << clientSocket.getPeerAddress() << ":" << clientSocket.getPeerPort() << std::endl;
}


void ChatServer::start() {
    m_serverSocket.create();

    if (!m_serverSocket.bind(m_port)) {
        std::cerr << "Failed to bind socket to port " << m_port << "." << std::endl;
        return;
    }

    if (!m_serverSocket.listen()) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return;
    }

    std::cout << "Server listening on port " << m_port << "." << std::endl;

    while (true) {
        SocketWrapper clientSocket;

        if (!m_serverSocket.accept(clientSocket)) {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }

        std::cout << "Client connected: " << clientSocket.getPeerAddress() << ":" << clientSocket.getPeerPort() << std::endl;

        // Start a new thread to handle the client connection
        std::thread clientThread(&ChatServer::handleClient, this, clientSocket);
        clientThread.detach(); // Allow thread to run independently
    }
}

void ChatServer::handleIoTCommand(const std::string& command) {
    if (!m_iotComm.connect()) {
        std::cerr << "Failed to connect to IoT device." << std::endl;
        return;
    }

    if (m_iotComm.sendCommand(command) < 0) {
        std::cerr << "Failed to send command to IoT device." << std::endl;
        return;
    }

    std::string response;
    if (m_iotComm.receiveResponse(response, 1024) < 0) {
        std::cerr << "Failed to receive response from IoT device." << std::endl;
    } else {
        std::cout << "IoT device response: " << response << std::endl;
    }

    m_iotComm.disconnect();
}