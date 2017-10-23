#pragma once
#include "../EGGIN/api.h"
#include "../EGGIN/gamelib.h"

#ifdef __linux__ 
#define EXPORT
#elif _WIN32
#define EXPORT __declspec( dllexport ) 
#endif

extern "C"
{
	int EXPORT Game_Main(engineapi* api, gamelib::api_s& game_api);
}