#pragma once
#include "../EGGIN/gameobject.h"
#include "../EGGIN/api.h"
#include "../EGGIN/common.h"
#include "blocks.h"

struct block_data {
	short int bid = 0;
	map<char, string> *data = nullptr;
};

class Chunk : public GameObject
{
private:
	block_data blocks[16][16][16];
	render::mesh mesh;
public:
	int X, Y, Z;
	Chunk(int x, int y, int z)
	{
		mesh = render::mesh();
		mesh.mat = blocks::atlas::mat;
		X = x;
		Y = y;
		Z = z;
	}

	~Chunk()
	{
		free(mesh.vertices);
		free(mesh.uvs);
	}

	void generate();
	void build();
	block_data* getBlock(int x, int y, int z);
	void draw3D() override
	{
		api->render.api->mesh.draw(&this->mesh, this->getGlobalPosition(), vec3());
	}
};