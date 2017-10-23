#include "console.h"
#include "libwork.h"
#include "host.h"
#include "api.h"
#include "gamelib.h"

static lib::instance game_lib;
typedef void(*gameMain_t)(engineapi* api, gamelib::api_s& game_api);
static gameMain_t Game_Main;
gamelib::api_s gamelib::rApi;

void gamelib::init()
{
	console::dev("Loading game library");
	if ((game_lib = lib::open("gamelib.dll")) == NULL)
		host::criticalError("Unable to load the game library");

	if ((Game_Main = (gameMain_t)lib::addr(game_lib, "Game_Main")) == NULL)
		host::criticalError("Incorrect game library");
	console::dev("...\n");

	Game_Main(api, gamelib::rApi);
	gamelib::rApi.init();
}

void gamelib::start()
{
	gamelib::rApi.start();
}
