#pragma once

#include "pch.h"

#include "ResourceCleanupTemplate.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

MAKE_RESOURCE_CLASS(Window, SDL_Window*, nullptr, SDL_DestroyWindow(resource))

MAKE_CLEANUP_CLASS(SDL_Library, SDL_Quit())
MAKE_CLEANUP_CLASS(SDL_IMG_Library, IMG_Quit())
MAKE_CLEANUP_CLASS(SDL_TTF_Library, TTF_Quit())