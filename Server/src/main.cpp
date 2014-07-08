#include "pch.h"

#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		std::shared_ptr<std::ostream> sharedCout(&std::cout, [](std::ostream* p){});
		logger.setStream(Severity::fatal, sharedCout);

		std::cout << "This is the server!\n" << std::endl;
	}
	catch(std::exception e)
	{
		logger.log(Severity::fatal, "main1", "Uncaught exception: ", e.what());
	}
	catch(...)
	{
		logger.log(Severity::fatal, "main2", "Uncaught unknown exception");
	}

	return 0;
}