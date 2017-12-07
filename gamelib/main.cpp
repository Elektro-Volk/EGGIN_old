#include "main.h"
#include "../EGGIN/api.h"
#include "../EGGIN/meshrenderer.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "blocks.h"
#include "World.h"
#include "WorldGenerator.h"
#include "MainMenu.h"
#include <time.h>

World* thisWorld;
WorldGenerator *generator;

void init() 
{
	
}

void startGame() {
	generator = new WorldGenerator(rand());
	Player *p = new Player(rand()%200-100, 50.0f, rand() % 200 - 100);
	api->gameobject.reg(p);
	api->render.camera->parent = p;	
	api->render.camera->setLocalPosition(vec3(0.f, 0.8f, 0.f));
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

	//new MainMenu(api->render.camera);
	startGame();
}



void update() {
	
}