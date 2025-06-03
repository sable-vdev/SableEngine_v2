#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <source_location>
#undef ERROR

enum LogLevel
{
	DEBUG = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3
};

class Logger
{
public:
	static const LogLevel showMessage = DEBUG;
	static void Log(LogLevel logLevel, const std::string& message, const std::source_location& location = std::source_location::current());
	static void Log(LogLevel logLevel, const unsigned char character, const std::source_location& location = std::source_location::current());
private:
	static std::string LogLevelToString(LogLevel logLevel);
	Logger() = delete;
	~Logger() = delete;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};
