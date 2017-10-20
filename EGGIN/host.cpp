// Init systems
#include "console.h"
#include "render.h"
// ------------
#include "api.h"
#include "SDL.h"
#include "host.h"

// API
engineapi api;

void host::initEngine(int argc, char **argv)
{
	// Init API
	api = {
		{// Console
			console::log,
			console::dev,
		}
	};
	//__________________________
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return;
	}

	console::init();
	render::init();

	// Start
	host::startEngine();
}

void host::startEngine()
{
	render::start();
}

void host::frameLoop()
{
	while (true)
	{

	}
}

void host::criticalError(string error)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "EGGIN Error", error.c_str(), NULL);
	exit(-1);
}