#include "pch.h"
#include <fstream>
#include <iostream>

#include "SDL.h"

int main(int argc, char** argv)
{
	/*
	spam = 0,
	info,
	warning,
	error,
	fatal,

	*/
	try
	{
		using namespace std::chrono;
		
		std::shared_ptr<std::ostream> sharedCout(&std::cout, [](std::ostream* p){});
		std::shared_ptr<std::ofstream> sharedErrorFile(new std::ofstream("error.txt"));
		std::shared_ptr<std::ofstream> sharedFatalFile(new std::ofstream("fatal.txt"));

		logger.setStream(Severity::spam, nullptr);
		logger.setStream(Severity::info, sharedCout);
		logger.setStream(Severity::warning, sharedCout);
		logger.setStream(Severity::error, sharedErrorFile);
		logger.setStream(Severity::fatal, sharedFatalFile);

		logger.log(Severity::spam, "mainSpam", "SPAM message");
		logger.log(Severity::spam, "mainSpam", "");
		logger.log(Severity::info, "mainInfo", "this is a message");
		logger.log(Severity::info, "mainInfo", "");
		logger.log(Severity::warning, "mainWarning","this is a message");
		logger.log(Severity::warning, "mainWarning", "");
		logger.log(Severity::error, "mainError", "this is a message");
		logger.log(Severity::error, "mainError", "");
		logger.log(Severity::fatal, "mainFatal", "fatal: this is a\t message");
		logger.log(Severity::fatal, "mainFatal", "");

		
		logger.log(Severity::warning, "tag", "Tina is ", 21, " years old", '!');
		

		std::cout << "This is the client!\n" << std::endl;

		if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Failed to initialize SDL");
		SDL_Library sdl_library;

		if (IMG_Init(0) != 0)
			throw std::runtime_error("Failed to initialize SDL_image");
		SDL_IMG_Library sdl_img_library;

		if (TTF_Init() != 0)
			throw std::runtime_error("Failed to initialize SDL_ttf");
		SDL_TTF_Library sdl_ttf_library;

		Window window = SDL_CreateWindow("Tina game!", 50, 50, 800, 600, 0);

		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{

			case SDL_QUIT:
				goto end;
			}
		}
		
	end:;
	}
	catch(std::exception e)
	{
		logger.log(Severity::fatal, "main", "Uncaught exception: ", e.what());
	}
	catch(...)
	{
		logger.log(Severity::fatal, "main", "Uncaught unknown exception");
	}

	return 0;
}