// Message.cpp

#include "Message.h"

Message::Message(const std::string& from, const std::string& content)
    : m_from(from), m_content(content), m_time(std::chrono::system_clock::now()) {}

std::string Message::getFrom() const {
    return m_from;
}

std::string Message::getContent() const {
    return m_content;
}

std::chrono::system_clock::time_point Message::getTime() const {
    return m_time;
}
