#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "input.h"
#include <windows.h>

const Uint8 *keystate;
int input::curX, input::curY;
int input::spdX, input::spdY;

void input::frame()
{
	keystate = SDL_GetKeyboardState(0);
	// Mouse pos
	POINT pt;
	GetCursorPos(&pt);

	spdX = pt.x - curX;
	spdY = pt.y - curY;

	curX = pt.x;
	curY = pt.y;
}

bool input::isKey(int code)
{
	return keystate[code];
}

bool input::isMouseKey(int code)
{
	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(code);
}

void input::getMouseSpeed(int &x, int &y)
{
	x = spdX;
	y = spdY;
}
