#include "IoTCommunication.h"

IoTCommunication::IoTCommunication() : m_host(""), m_port(0) {}

IoTCommunication::IoTCommunication(const std::string& host, unsigned short port)
    : m_host(host), m_port(port) {}

IoTCommunication::~IoTCommunication() {
    disconnect();
}

bool IoTCommunication::connect() {
    if (!m_iotSocket.create()) {
        return false;
    }
    return m_iotSocket.connect(m_host, m_port);
}

bool IoTCommunication::disconnect() {
    m_iotSocket.close();
    return true;
}

int IoTCommunication::sendCommand(const std::string& command) {
    return m_iotSocket.send(command);
}

int IoTCommunication::receiveResponse(std::string& response, int maxBytes) {
    return m_iotSocket.receive(response, maxBytes);
}

void IoTCommunication::setHostAndPort(const std::string& host, unsigned short port) {
    m_host = host;
    m_port = port;
}