#include "ChatClient.h"
#include <iostream>
#include <thread>

ChatClient::ChatClient(const std::string& host, unsigned short port) : m_host(host), m_port(port) {}

ChatClient::~ChatClient() {}

void ChatClient::handleServerMessages() {
    std::string message;
    int receivedBytes;

    while (true) {
        receivedBytes = m_clientSocket.receive(message, 1024);

        if (receivedBytes > 0) {
            std::cout << "Server: " << message << std::endl;
        } else {
            std::cerr << "Connection closed by server." << std::endl;
            break;
        }
    }
}

void ChatClient::start() {
    m_clientSocket.create();

    if (!m_clientSocket.connect(m_host, m_port)) {
        std::cerr << "Failed to connect to server." << std::endl;
        return;
    }

    std::cout << "Connected to server: " << m_host << ":" << m_port << std::endl;

    std::thread serverMessagesThread(&ChatClient::handleServerMessages, this);

    std::string input;
    while (true) {
        std::getline(std::cin, input);

        if (input == "/quit") {
            break;
        }

        if (!m_clientSocket.send(input)) {
            std::cerr << "Failed to send message to server." << std::endl;
        }
    }

    serverMessagesThread.join();
    m_clientSocket.close();
}
