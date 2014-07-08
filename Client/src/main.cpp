#include "pch.h"
#include <fstream>
#include <iostream>

#include "SDL.h"
#include "Renderer.h"

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
		logger.setStream(Severity::fatal, sharedCout);

		
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

		Renderer renderer("Tina game!", 1024, 768, Renderer::WindowType::windowed);
		renderer.show();

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
		logger.log(Severity::fatal, "main1", "Uncaught exception: ", e.what());
	}
	catch(...)
	{
		logger.log(Severity::fatal, "main2", "Uncaught unknown exception");
	}

	return 0;
}