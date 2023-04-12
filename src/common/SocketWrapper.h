#pragma once

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

class SocketWrapper {
public:
    SocketWrapper();
    ~SocketWrapper();

    bool create();
    bool bind(unsigned short port);
    bool listen(int maxBacklog = 5);
    bool accept(SocketWrapper& clientSocket);
    bool connect(const std::string& host, unsigned short port);
    int send(const std::string& message);
    int receive(std::string& message, int maxBytes);
    void close();

    std::string getPeerAddress() const;
    unsigned short getPeerPort() const;

private:
    int m_socketHandle;
    sockaddr_in m_address;
};
