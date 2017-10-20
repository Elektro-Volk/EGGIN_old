#pragma once
#ifdef __linux__ 
#include <dlfcn.h> 
#elif _WIN32 
#include <Windows.h>
#endif

namespace lib
{
#ifdef __linux__ 
	typedef void* instance;
#elif _WIN32 
	typedef HINSTANCE instance;
#endif

	instance open(char* name);
	void* addr(instance& lib, char *function);
	void close(instance &lib);
}