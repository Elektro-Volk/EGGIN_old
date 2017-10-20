#include "libwork.h"

#ifdef __linux__ 
lib::instance lib::open(char* name)
{
	return dlopen(name, RTLD_NOW);
}

void* lib::addr(lib::instance& lib, char *function)
{
	return dlsym(lib, function);
}

void lib::close(lib::instance &lib)
{
	dlclose(name, RTLD_NOW);
}
#elif _WIN32 

lib::instance lib::open(char* name)
{
	return LoadLibraryA(name);
}

void* lib::addr(lib::instance& lib, char *function)
{
	return GetProcAddress(lib, function);
}

void lib::close(lib::instance &lib)
{
	FreeLibrary(lib);
}
#endif