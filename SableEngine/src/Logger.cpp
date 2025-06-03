#include "Logger.hpp"

void Logger::Log(LogLevel logLevel, const std::string& message, const std::source_location& location)
{
	if (logLevel >= showMessage)
	{
		std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
		std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
			<< location.function_name()
			<< "[" << LogLevelToString(logLevel) << "] " << message << std::endl;
	}
}

void Logger::Log(LogLevel logLevel, const unsigned char character, const std::source_location& location)
{
	std::string output = "";
	output += character;
	if (logLevel >= showMessage)
	{
		std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
		std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
			<< location.function_name()
			<< "[" << LogLevelToString(logLevel) << "] " << output << std::endl;
	}
}

std::string Logger::LogLevelToString(LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::DEBUG:
		return "DEBUG";
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARNING:
		return "WARNING";
	case LogLevel::ERROR:
		return "ERROR";
	default:
		return "UNKNOWN";
	}
}