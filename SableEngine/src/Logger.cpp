#include "Logger.hpp"

void Logger::Log(LogLevel logLevel, const std::string& message, const std::source_location& location)
{
	std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
	std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
	<< location.function_name() << "(" << location.line() << ";" << location.column() << ")"
	<< "[" << LogLevelToString(logLevel) << "] " << message << std::endl;

}

void Logger::Log(LogLevel logLevel, const unsigned char& character, const std::source_location& location)
{
	std::string output = "";
	output += character;
	std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
	std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
		<< location.function_name() << "(" << location.line() << ";" << location.column() << ")"
		<< "[" << LogLevelToString(logLevel) << "] " << output << std::endl;
}

void Logger::Log(LogLevel logLevel, const wchar_t* character, const std::source_location& location)
{
	std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
	std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
		<< location.function_name() << "(" << location.line() << ";" << location.column() << ")"
		<< "[" << LogLevelToString(logLevel) << "] ";
	std::wprintf(L"%s\n", character);
}

void Logger::Log(LogLevel logLevel, const std::wstring& message, const std::source_location& location)
{
	std::chrono::system_clock::time_point timenow = std::chrono::system_clock::now();
	std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%S}", timenow) << "]"
		<< location.function_name() << "(" << location.line() << ";" << location.column() << ")"
		<< "[" << LogLevelToString(logLevel) << "] ";
	std::wprintf(L"%s\n", message.c_str());
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