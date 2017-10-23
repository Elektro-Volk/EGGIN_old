#include "blocks.h"

vector<blocks::block*> blocks::blocks;

material* mat;
int blocks::atlas::cX = 16;
int blocks::atlas::cY = 16;

float blocks::atlas::uX;
float blocks::atlas::uY;


void buildTex(blocks::block* b)
{
	for (auto &t : b->texture) {
		t.ux = blocks::atlas::uX * t.px;
		t.uy = blocks::atlas::uY * t.py;
	}
}

void blocks::init()
{
	mat = api->material.create("atlas.mat");

	blocks::atlas::uX = 1.0 / blocks::atlas::cX;
	blocks::atlas::uY = 1.0 / blocks::atlas::cY;
	blocks::blocks.push_back(NULL);// Wind :D

	blocks::block* b = new blocks::block();
	b->texture = { {3,0}, {3,0}, {3,0}, {3,0}, {0,0}, {2,0} };
	buildTex(b);
	blocks::blocks.push_back(b);
}

vector<float> blocks::atlas::getUV(int block, int tid)
{
	float x2 = blocks[block]->texture[tid].ux;
	float y2 = blocks[block]->texture[tid].uy;
	float x = x2 + blocks::atlas::uX;
	float y = y2 + blocks::atlas::uY;
	
	return { x, y, x2, y, x2, y2, x2, y2, x, y2, x, y };
}
