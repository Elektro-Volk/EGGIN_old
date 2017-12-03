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
	b->texture = { {3,0}, {3,0}, {3,0}, {3,0}, {0,0}, {2,0} };
	buildTex(b);
	blocks::blocks.push_back(b);

	blocks::block* b2 = new blocks::block();
	b2->texture = { { 12,2 },{ 13,2 },{ 13,2 },{ 13,2 },{ 14,4 },{ 14,4 } };
	buildTex(b2);
	blocks::blocks.push_back(b2);
}

float *blocks::atlas::getUV(block* block, int tid)
{
	float x2 = block->texture[tid].ux;
	float y2 = block->texture[tid].uy;
	float x = x2 + blocks::atlas::uX;
	float y = y2 + blocks::atlas::uY;
	
	return new float[12]{ x, y, x2, y, x2, y2, x2, y2, x, y2, x, y };
}