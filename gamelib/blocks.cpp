#include "blocks.h"

vector<blocks::block*> blocks::blocks;

material* blocks::atlas::mat;
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
	blocks::atlas::mat = api->material.create("atlas.mat");

	blocks::atlas::uX = 1.0 / blocks::atlas::cX;
	blocks::atlas::uY = 1.0 / blocks::atlas::cY;
	blocks::blocks.push_back(NULL);// Wind :D

	blocks::block* b = new blocks::block();
	//             FORW   BACK   LEFT   RIGHT  TOP    BOTOM
	// Grass - 1
	b->texture = { {3,0}, {3,0}, {3,0}, {3,0}, {0,0}, {2,0} };
	buildTex(b);
	blocks::blocks.push_back(b);
	// Dirt - 2
	blocks::block* dirt = new blocks::block();
	dirt->texture = { { 2,0 },{ 2,0 },{ 2,0 },{ 2,0 },{ 2,0 },{ 2,0 } };
	buildTex(dirt);
	blocks::blocks.push_back(dirt);
	// Rock - 3
	blocks::block* rock = new blocks::block();
	rock->texture = { { 1,0 },{ 1,0 },{ 1,0 },{ 1,0 },{ 1,0 },{ 1,0 } };
	buildTex(rock);
	blocks::blocks.push_back(rock);
	// Water - 4
	blocks::block* water = new blocks::block();
	water->texture = { { 13,12 },{ 13,12 },{ 13,12 },{ 13,12 },{ 13,12 },{ 13,12 } };
	buildTex(water);
	blocks::blocks.push_back(water);
	// Sand - 5
	blocks::block* sand = new blocks::block();
	sand->texture = { { 2,1 },{ 2,1 },{ 2,1 },{ 2,1 },{ 2,1 },{ 2,1 } };
	buildTex(sand);
	blocks::blocks.push_back(sand);
	// Wood - 6
	blocks::block* wood = new blocks::block();
	wood->texture = { { 4,0 },{ 4,0 },{ 4,0 },{ 4,0 },{ 4,0 },{ 4,0 } };
	buildTex(wood);
	blocks::blocks.push_back(wood);
}

float *blocks::atlas::getUV(block* block, int tid)
{
	float x2 = block->texture[tid].ux;
	float y2 = block->texture[tid].uy;
	float x = x2 + blocks::atlas::uX;
	float y = y2 + blocks::atlas::uY;
	
	return new float[12]{ x, y, x2, y, x2, y2, x2, y2, x, y2, x, y };
}