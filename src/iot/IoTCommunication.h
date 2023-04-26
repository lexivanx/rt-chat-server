#pragma once

#include <string>
#include "../common/SocketWrapper.h"

class IoTCommunication {
public:
    IoTCommunication();
    IoTCommunication(const std::string& host, unsigned short port);
    ~IoTCommunication();

    bool connect();
    bool disconnect();
    int sendCommand(const std::string& command);
    int receiveResponse(std::string& response, int maxBytes);
    void setHostAndPort(const std::string& host, unsigned short port);

private:
    SocketWrapper m_iotSocket;
    std::string m_host;
    unsigned short m_port;
};
