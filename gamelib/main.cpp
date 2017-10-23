#include "main.h"
#include "../EGGIN/api.h"
#include "../EGGIN/meshrenderer.hpp"
#include "Player.hpp"
#include "Skybox.hpp"
#include "Chunk.h"
#include "blocks.h"

void init() 
{
	
}

void start() 
{
	blocks::init();
	Skybox *sky = new Skybox();
	api->gameobject.reg(sky);

	meshrenderer *mr = new meshrenderer();
	mr->mesh = api->models.load("cube.egg");
	mr->setGlobalPosition(vec3(0, 0, 50));
	api->gameobject.reg(mr);

	Player *p = new Player();
	api->gameobject.reg(p);
	api->render.camera->parent = p;	

	Chunk *c = new Chunk();
	api->gameobject.reg(c);
}

void update() {}