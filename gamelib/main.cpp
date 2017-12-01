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

bool check(float Dx, float Dy, float Dz)
{ 
	vec3 p(floor(Dx / 16.f), floor(Dy / 16.f), floor(Dz / 16.f));
	if (p.y < 0 || p.y > 7)
		return false;
	if (auto C = thisWorld->getChunk(p.x, p.y, p.z))
	{
		int x, y, z;
		x = (Dx - floor(Dx / 16.f) * 16);
		y = (Dy - floor(Dy / 16.f) * 16);
		z = (Dz - floor(Dz / 16.f) * 16);
		return C->getBlock(x, y, z)->bid != 0;
	}
	return false; 
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

	Player *p = new Player(0.0f, 25.0f, 0.0f);
	api->gameobject.reg(p);
	api->render.camera->parent = p;	
	api->render.camera->setLocalPosition(vec3(0.f, 1.8f, 0.f));

	thisWorld = new World();
	api->gameobject.reg(thisWorld);
	thisWorld->setPlayer(p);
	thread t = thread(worldLoop);
	t.detach();
}



void update() {}