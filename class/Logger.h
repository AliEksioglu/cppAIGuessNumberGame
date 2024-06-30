#ifndef LOGGER_H
#define LOGGER_H

#define RESET "\033[0m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_WHITE "\033[37m"

#include <string>
#include <iostream>

class Logger
{

public:
    enum class MessageType
    {
        DEFAULT,
        INFO,
        WARN,
        GREEN
    };

    void message(const std::string message, MessageType messageType = MessageType::DEFAULT, const bool _endl = false) const
    {
        auto color = COLOR_WHITE;
        switch (messageType)
        {
        case MessageType::INFO:
            color = COLOR_CYAN;
            break;
        case MessageType::WARN:
            color = COLOR_YELLOW;
            break;
        case MessageType::GREEN:
            color = COLOR_GREEN;
            break;
        default:
            color = COLOR_WHITE;
            break;
        }

        if (_endl)
        {
            std::cout << color << message << RESET << std::endl;
        }
        else
        {
            std::cout << color << message << RESET;
        }
    }
};

#endif