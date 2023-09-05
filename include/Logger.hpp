#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <vector>

enum LogType
{
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

struct LogEntry
{
    LogType type;
    std::string message;
    tm timestamp;
};

class Logger
{
  public:
    static std::vector<LogEntry> messages;
    static void log(const std::string &message);
    static void error(const std::string &message);
    static void warn(const std::string &message);
};

#endif
