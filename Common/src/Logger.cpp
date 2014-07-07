#include "pch.h"
#include <iomanip>
#include "Logger.h"

Logger logger;

Logger::Logger()
{
	streams = std::vector<std::shared_ptr<std::ostream>>(static_cast<int>(Severity::numElements));
}

void Logger::log(Severity severity, const std::string& tag, const std::string& message)
{
	if (streams[static_cast<int>(severity)] == NULL)
	{
		return;
	}

	//get current time of of log
	using namespace std::chrono;
	system_clock::time_point currentTime = system_clock::now();
	auto currentClockTime = std::chrono::system_clock::to_time_t(currentTime);
	struct tm ptm;
	localtime_s(&ptm, &currentClockTime);

	(*streams[static_cast<int>(severity)]) << std::put_time(&ptm, "%H:%M:%S") << " " + tag + ": " + message << std::endl;
	
	
}

void Logger::setStream(Severity severity, std::shared_ptr<std::ostream> stream)
{
	streams[static_cast<int>(severity)] = stream;
}
