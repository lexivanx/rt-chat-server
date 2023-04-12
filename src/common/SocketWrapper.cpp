#include <string>
#include <netinet/in.h>

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

    std::string getPeerAddress() const;
    unsigned short getPeerPort() const;

    void close();

private:
    int m_socketHandle;
    sockaddr_in m_address;
};

std::string SocketWrapper::getPeerAddress() const {
    char addressBuffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(m_address.sin_addr), addressBuffer, INET_ADDRSTRLEN);
    return std::string(addressBuffer);
}

unsigned short SocketWrapper::getPeerPort() const {
    return ntohs(m_address.sin_port);
}

void SocketWrapper::close() {
#ifdef _WIN32
    closesocket(m_socketHandle);
#else
    ::close(m_socketHandle);
#endif
}
