#include "pch.h"

#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		std::cout << "This is the server!\n" << std::endl;
	}
	catch(std::exception e)
	{
		std::cout << "Uncaught exception: " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Uncaught unknown exception" << std::endl;
	}

	return 0;
}