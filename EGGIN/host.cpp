// Init systems
#include "console.h"
// ------------
#include "host.h"

void host::initEngine(int argc, char **argv)
{
	console::init();
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