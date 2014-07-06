#include "pch.h"

#include "Logger.h"

Logger logger;

class LoggerCreator
{
public:
	//Creates the logger object
	LoggerCreator()
	{

	}
};
static LoggerCreator loggerCreator;

void Logger::log(Severity severity, const std::string& tag, const std::string& message)
{

}

void setStream(Severity severity, std::unique_ptr<std::ostream> stream)
{

}
