#pragma once
#include "../EGGIN/gameobject.h"
#include "../EGGIN/api.h"
#include "../EGGIN/common.h"

struct block_data {
	int bid = 0;
	map<int, string> data;
};

class Chunk : public GameObject
{
private:
	block_data blocks[16][16][16];
	render::mesh mesh;
public:
	Chunk()
	{
		mesh = render::mesh();
		mesh.mat = api->material.create("atlas.mat");
		generate();
		build();
	}

	void generate();
	void build();
	void draw3D() override
	{
		api->render.api->mesh.draw(&this->mesh, this->getGlobalPosition(), vec3());
	}
};