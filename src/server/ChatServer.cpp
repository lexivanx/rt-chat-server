#include "ChatServer.h"
#include "SocketWrapper.h"

#include <iostream>
#include <thread>

ChatServer::ChatServer(unsigned short port) : m_port(port) {}

ChatServer::~ChatServer() {}

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
