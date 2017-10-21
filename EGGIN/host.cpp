// Init systems
#include "console.h"
#include "render.h"
#include "gameobject.h"
// ------------
#include "api.h"
#include "SDL.h"
#include "host.h"

#undef main

// API
engineapi api;

void host::initEngine(int argc, char **argv)
{
	// Init API
	api = {
		{// Console
			console::log,
			console::dev,
		},
		{// Host
			host::criticalError
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
		render::rApi.main.preFrame();
		for (auto go : gameobject::gameobjects)
			go.second->update();
		render::rApi.main.postFrame();
	}
}

void host::criticalError(string error)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "EGGIN Error", error.c_str(), NULL);
	exit(-1);
}