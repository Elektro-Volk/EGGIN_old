#include "lib.h"
#include "host.h"

int EXPORT Host_Main(int argc, char **argv)
{
	host::initEngine(argc, argv);
	host::frameLoop();
	return 1;
}