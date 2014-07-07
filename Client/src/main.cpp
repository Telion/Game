#include "pch.h"

#include <iostream>
#include "SDL.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
	try
	{
		std::cout << "This is the client!\n" << std::endl;

		if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Failed to initialize SDL");
		SDL_Library sdl_library;

		if(IMG_Init(0) != 0)
			throw std::runtime_error("Failed to initialize SDL_image");
		SDL_IMG_Library sdl_img_library;

		if(TTF_Init() != 0)
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
		std::cout << "Uncaught exception: " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Uncaught unknown exception" << std::endl;
	}

	return 0;
}