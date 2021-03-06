#pragma once

#include "pch.h"

class ostream;

enum class Severity
{
	spam = 0,
	info,
	warning,
	error,
	fatal,

	numElements
};

class Logger
{
	//members
	std::vector<std::shared_ptr<std::ostream>> streams;

	//functions
	template <typename T>
	void log_internal(Severity severity, const std::string& tag, std::stringstream& stream, T arg)
	{
		stream << arg;
		log(severity, tag, stream.str());
	}

	template <typename T, typename... Args>
	void log_internal(Severity severity, const std::string& tag, std::stringstream& stream, T arg, Args ...args)
	{
		stream << arg;
		log_internal(severity, tag, stream, args...);
	}


	Logger(const Logger& rhs);
	Logger& operator =(const Logger& rhs);
	Logger(Logger&& rhs);
	Logger& operator =(Logger&& rhs);

public:
	Logger();

	void log(Severity severity, const std::string& tag, const std::string& message);
	void setStream(Severity severity, std::shared_ptr<std::ostream> stream);


	template <typename T>
	void log(Severity severity, const std::string& tag, T arg)
	{
		std::stringstream ss;
		log_internal(severity, tag, ss, arg);
	}

	template <typename T, typename... Args>
	void log(Severity severity, const std::string& tag, T arg, Args ...args)
	{
		std::stringstream ss;
		log_internal(severity, tag, ss, arg, args...);
	}
};

extern Logger logger;
