#pragma once

#include "../common/SocketWrapper.h"

class ChatClient {
public:
    ChatClient(const std::string& host, unsigned short port);
    ~ChatClient();

    void start();
    void handleServerMessages();

private:
    SocketWrapper m_clientSocket;
    std::string m_host;
    unsigned short m_port;
};
