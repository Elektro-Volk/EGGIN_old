#pragma once
#ifdef __linux__ 
	#define EXPORT
#elif _WIN32
	#define EXPORT	 __declspec( dllexport ) 
#endif

extern "C" 
{
	int EXPORT Host_Main(int argc, char **argv);
}