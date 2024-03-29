// Init systems
#include "console.h"
#include "render.h"
#include "gamelib.h"
#include "gameobject.h"
#include "models.h"
#include "input.h"
// ------------
#include "api.h"
#include "SDL.h"
#include "host.h"

#undef main

// API
engineapi* api;

void host::initEngine(int argc, char **argv)
{
	// Init API
	api = new engineapi({
		{// Console
			console::log,
			console::dev,
		},
		{// Host
			host::criticalError
		},
		{// Models
			models::load
		},
		{// Gameobjects
			gameobject::reg,
			gameobject::unreg
		},
		{ // material
			material::create
		},
		{ // render
			&render::rApi,
			render::camera
		},
		{ // input
			input::isKey,
			input::isMouseKey,
			input::getMouseSpeed,
			input::setLockCursor,
			input::isKeyChanged,
			input::isMouseKeyChanged
		},
		{ // Textures
			texture::load,
			texture::unload
		}
	});
	//__________________________
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return;
	}

	console::init();
	render::init();
	gamelib::init();

	// Start
	host::startEngine();
}

void host::startEngine()
{
	render::start();
	gamelib::start();
}

void host::frameLoop()
{
	while (true)
	{
		input::frame();
		gamelib::rApi.update();
		gameobject::call(&GameObject::update);
		
		render::frame();
		gameobject::call(&GameObject::draw3D);
		render::rApi.main.set2d();
		gameobject::call(&GameObject::draw2D);
		render::rApi.main.postFrame();
	}
}

void host::criticalError(string error)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "EGGIN Error", error.c_str(), NULL);
	exit(-1);
}