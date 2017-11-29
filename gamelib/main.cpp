#include "main.h"
#include "../EGGIN/api.h"
#include "../EGGIN/meshrenderer.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "Chunk.h"
#include "blocks.h"
#include "World.h"
#include <thread>

World* thisWorld;

void init() 
{
	
}

void worldLoop()
{
	//for (int x = -2; x < 2; x++)
		//for (int z = -2; z < 2; z++)
		//	thisWorld->buildColumn(x, z);
	while (true) {
		thisWorld->tUpdate();
	}
}


void start() 
{
	blocks::init();
	Skybox *sky = new Skybox();
	api->gameobject.reg(sky);

	Player *p = new Player();
	api->gameobject.reg(p);
	api->render.camera->parent = p;	
	p->setGlobalPosition({ 0.0f, 25.0f, 0.0f });

	thisWorld = new World();
	api->gameobject.reg(thisWorld);
	thisWorld->setPlayer(p);
	thread t = thread(worldLoop);
	t.detach();
}



void update() {}