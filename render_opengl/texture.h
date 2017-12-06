#pragma once
#include "SDL.h"
#include "SDL_surface.h"

namespace texture
{
	int create (void* data);
	void free (int tid);
}