#include "main.h"
#include "../EGGIN/api.h"
#include "../EGGIN/meshrenderer.h"

void init() {}
void start() 
{
	meshrenderer *mr = new meshrenderer();
	mr->mesh = api.models.load("cube.obj");
	mr->mesh->mat = api.material.create("default.mat");
	mr->setGlobalPosition(vec3(0, 0, -50));
	api.gameobject.reg(mr);
}

void meshrenderer::update() {}

void update() {}