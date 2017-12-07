#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "input.h"
#include <windows.h>
#include <iostream>

const Uint8 *keystate;
const Uint8 *old_keystate;
Uint8 mousestate;
Uint8 old_mousestate;
int input::curX, input::curY;
int input::spdX, input::spdY;
bool input::lockCursor;

void input::frame()
{
	old_keystate = keystate;
	old_mousestate = mousestate;
	keystate = SDL_GetKeyboardState(0);
	mousestate = SDL_GetMouseState(NULL, NULL);
	// Mouse pos
	POINT pt;
	GetCursorPos(&pt);

	spdX = pt.x - curX;
	spdY = pt.y - curY;

	curX = pt.x;
	curY = pt.y;

	if (lockCursor) {
		curX = 900;
		curY = 500;
		SetCursorPos(900, 500);
	}
}

bool input::isKey(int code)
{
	return keystate[code];
}

bool input::isKeyChanged(int code, bool pressed)
{
	return old_keystate[code] != keystate[code] && keystate[code] == pressed;
}

bool input::isMouseKeyChanged(int code, bool pressed)
{
	return ((mousestate & SDL_BUTTON(code)) != (old_mousestate & SDL_BUTTON(code)))
		&& ((bool)(mousestate & SDL_BUTTON(code)) == pressed);
}

bool input::isMouseKey(int code)
{
	return mousestate & SDL_BUTTON(code);
}

void input::getMouseSpeed(int &x, int &y)
{
	x = spdX;
	y = spdY;
}

void input::setLockCursor(bool lock)
{
	lockCursor = lock;
}
