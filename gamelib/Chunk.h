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
	render::mesh mesh;
public:
	block_data blocks[16][16][16];
	bool nB = true;
	int X, Y, Z;

	Chunk(int x, int y, int z)
	{
		mesh = render::mesh();
		mesh.texture = blocks::atlas::texture;
		mesh.rtype = render::mesh::RT::quads;
		X = x;
		Y = y;
		Z = z;
	}

	~Chunk()
	{
		free(mesh.vertices);
   		free(mesh.uvs);
	}

	void build();
	block_data* getBlock(int x, int y, int z);
	void draw3D() override
	{
		if(!nB)
			api->render.api->mesh.draw(&this->mesh, this->getGlobalPosition(), vec3());
	}
};