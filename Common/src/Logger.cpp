#include "pch.h"

#include "Logger.h"

Logger logger;

Logger::Logger()
{

}

void Logger::log(Severity severity, const std::string& tag, const std::string& message)
{

}

void setStream(Severity severity, std::unique_ptr<std::ostream> stream)
{

}
