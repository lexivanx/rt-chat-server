#pragma once

#include "SocketWrapper.h"

#include <string>

class ChatServer {
public:
    ChatServer(unsigned short port);
    ~ChatServer();

    void start();

private:
    unsigned short m_port;
    SocketWrapper m_serverSocket;

    void handleClient(SocketWrapper clientSocket);
};
