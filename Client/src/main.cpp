#include "pch.h"

#include "SDL2/SDL.h"
#include <iostream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/serialization.hpp"

class SerializableTest
{
public:
	int a;
	std::string str;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & a;
		ar & str;
	}
};

int main(int argc, char** argv)
{
	std::cout << "This is the client!\n" << std::endl;

	// Test the Boost library before creating a window.
	// This requires that boost::serialization was fixed manually.
	boost::archive::text_oarchive archive(std::cout);
	SerializableTest st;
	st.a = 25;
	st.str = "Hello, Chris!";
	archive & st;

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