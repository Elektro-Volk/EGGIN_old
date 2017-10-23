#pragma once
#include "../EGGIN/api.h"
#include "../EGGIN/render.h"

#ifdef __linux__ 
#define EXPORT
#elif _WIN32
#define EXPORT __declspec( dllexport ) 
#endif

extern "C"
{
	int EXPORT Render_Main(engineapi* api, render::api_s& render_api);
}