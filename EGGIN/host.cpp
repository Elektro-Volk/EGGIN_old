// Init systems
#include "console.h"
#include "render.h"
// ------------
#include "api.h"
#include "host.h"

// API
static engineapi api = {
	{// Console
		console::log,
		console::log,
		console::dev,
		console::dev,
	}
};

void host::initEngine(int argc, char **argv)
{
	console::init();
	render::init();
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