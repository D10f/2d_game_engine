#include "Logger/Logger.hpp"
#include <iomanip>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";

const std::string ISO8601_UTC_DATE_TIME = "%Y-%m-%dT%H:%M:%SZ";
const std::string ISO8601_UTC_DATE = "%Y-%m-%d";
const std::string ISO8601_UTC_TIME = "%H:%M:%SZ";
const std::string ISO8601_OFFSET_TIME = "%H:%M:%SZ%z";
const std::string ISO8601_OFFSET_DATE_TIME = "%Y-%m-%dT%H:%M:%SZ%z";
const std::string ISO8601_OFFSET_DATE = "%Y-%m-%d%z";

std::vector<LogEntry> Logger::messages;

void printMessage(const LogEntry &entry, int justify = 5)
{
    switch (entry.type)
    {
    case LOG_INFO:
        std::cout << BLUE << std::left << std::setw(justify) << "LOG";
        break;
    case LOG_WARN:
        std::cout << YELLOW << std::left << std::setw(justify) << "WARN";
        break;
    case LOG_ERROR:
        std::cout << RED << std::left << std::setw(justify) << "ERROR";
        break;
    }

    std::cout << " | " << std::put_time(&entry.timestamp, ISO8601_UTC_DATE_TIME.c_str()) << " - ";
    std::cout << entry.message << std::endl;
    std::cout << RESET;
}

void initEntry(const LogType &type, const std::string &message, LogEntry &entry)
{
    std::time_t t = std::time(nullptr);
    tm timestamp = *std::localtime(&t);

    entry.type = type;
    entry.message = message;
    entry.timestamp = timestamp;

    Logger::messages.push_back(entry);
}

void Logger::log(const std::string &message)
{
    LogEntry entry;
    initEntry(LOG_INFO, message, entry);
    printMessage(entry);
}

void Logger::warn(const std::string &message)
{
    LogEntry entry;
    initEntry(LOG_WARN, message, entry);
    printMessage(entry);
}

void Logger::error(const std::string &message)
{
    LogEntry entry;
    initEntry(LOG_ERROR, message, entry);
    printMessage(entry);
}
