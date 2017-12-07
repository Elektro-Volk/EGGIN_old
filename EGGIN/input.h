#pragma once
#include "SDL_scancode.h"
#include "SDL_mouse.h"

namespace input
{
	extern int curX, curY;
	extern int spdX, spdY;
	extern bool lockCursor;

	void frame();
	bool isKey(int code);
	bool isKeyChanged(int code, bool pressed);
	bool isMouseKeyChanged(int code, bool pressed);
	bool isMouseKey(int code);
	void getMouseSpeed(int &x, int &y);
	void setLockCursor(bool lock);
}