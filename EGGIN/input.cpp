#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "input.h"

const Uint8 *keystate;

void input::frame()
{
	keystate = SDL_GetKeyboardState(0);
}

bool input::isKey(int code)
{
	return keystate[code];
}

bool input::isMouseKey(int code)
{
	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(code);
}