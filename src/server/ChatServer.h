#pragma once

#include "../common/SocketWrapper.h"
#include "../iot/IoTCommunication.h"

#include <string>

class ChatServer {
public:
    ChatServer(unsigned short port);
    ~ChatServer();

    void start();

private:
    unsigned short m_port;
    SocketWrapper m_serverSocket;
    IoTCommunication m_iotComm;

    void handleClient(SocketWrapper clientSocket);
    void handleIoTCommand(const std::string& command);
    void loadIoTDeviceConfig(std::string& host, unsigned short& port);
};
