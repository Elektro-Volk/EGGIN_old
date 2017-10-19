#pragma once
#ifdef __linux__ 
	#include <dlfcn.h> 
	#define openlib(x) dlopen(x, RTLD_NOW) 
	#define closelib(x) dlclose(x)
	#define getaddr(x,y) dlsym(x, y)
	#define lib void* 
#elif _WIN32 
	#include <windows.h>
	#define openlib(x) LoadLibraryA(x) 
	#define closelib(x) FreeLibrary(x) 
	#define getaddr(x,y) GetProcAddress(x,y) 
	#define lib HINSTANCE 
#endif