#pragma once

#include <string>
#include <chrono>

class Message {
public:
    Message(const std::string& from, const std::string& content);
    std::string getFrom() const;
    std::string getContent() const;
    std::chrono::system_clock::time_point getTime() const;

private:
    std::string m_from;
    std::string m_content;
    std::chrono::system_clock::time_point m_time;
};
