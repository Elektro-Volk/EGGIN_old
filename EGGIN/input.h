#pragma once
#include "SDL_scancode.h"
#include "SDL_mouse.h"

namespace input
{
	void frame();
	bool isKey(int code);
	bool isMouseKey(int code);
}