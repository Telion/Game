#include "pch.h"

#include "SDL2/SDL.h"

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Tina game!", 50, 50, 800, 600, 0);
	
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

	return 0;
}