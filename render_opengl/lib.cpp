#include "main.h"
#include "lib.h"

engineapi engine;

int EXPORT Render_Main(engineapi& api, render::api_s& render_api)
{
	engine = api;
	render_api = {
		{
			createWindow,
			frame
			}
	};
	return 1;
}