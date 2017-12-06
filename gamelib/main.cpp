#include "main.h"
#include "../EGGIN/api.h"
#include "../EGGIN/meshrenderer.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "blocks.h"
#include "World.h"
#include "WorldGenerator.h"
#include "MainMenu.h"
#include <windows.h>

World* thisWorld;
WorldGenerator *generator;

void init() 
{
	
}

void startGame() {
	generator = new WorldGenerator(rand());
	Player *p = new Player(0.f, 25.0f, 0.f);
	api->gameobject.reg(p);
	api->render.camera->parent = p;	
	api->render.camera->setLocalPosition(vec3(0.f, 0.9f, 0.f));
	thisWorld = new World(generator, p);
	api->input.setLockCursor(true);
}


void start() 
{
	blocks::init();
	srand(time(0));
	//

	Skybox *sky = new Skybox();
	api->gameobject.reg(sky);

	new MainMenu(api->render.camera);
	//startGame();
}



void update() {
	
}