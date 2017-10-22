#include "lib.h"
#include "main.h"

engineapi api;

int EXPORT Game_Main(engineapi& _api, gamelib::api_s& game_api)
{
	api = _api;
	game_api = {
		init,
		start,
		update
	};
	return 1;
}