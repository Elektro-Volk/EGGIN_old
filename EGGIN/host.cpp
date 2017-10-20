// Init systems
#include "console.h"
#include "render.h"
// ------------
#include "api.h"
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

}