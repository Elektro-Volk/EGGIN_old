#include "blocks.h"

vector<blocks::block*> blocks::blocks;

int blocks::atlas::texture;
int blocks::atlas::cX = 16;
int blocks::atlas::cY = 16;

float blocks::atlas::uX;
float blocks::atlas::uY;

void buildTex(blocks::block* b)
{
	b->tUVS = (float**)malloc(6 * sizeof(float*));
	for (int i = 0; i < 6; i++) {
		auto t = b->texture[i];
		t.ux = blocks::atlas::uX * t.px;
		t.uy = blocks::atlas::uY * t.py;
		// Make UV
		float x2 = t.ux;
		float y2 = t.uy;
		float x = x2 + blocks::atlas::uX;
		float y = y2 + blocks::atlas::uY;

		b->tUVS[i] = new float[8]{ x, y, x2, y, x2, y2, x, y2 };
	}
}

blocks::block* newBlock(
	blocks::tex _forward,
	blocks::tex _back,
	blocks::tex _left,
	blocks::tex _right,
	blocks::tex _top,
	blocks::tex _bottom
)
{
	blocks::block* b = new blocks::block();
	// Set textures
	b->texture[0] = _forward;
	b->texture[1] = _back;
	b->texture[2] = _left;
	b->texture[3] = _right;
	b->texture[4] = _top;
	b->texture[5] = _bottom;

	buildTex(b);
	blocks::blocks.push_back(b);
	return b;
}

void blocks::init()
{
	blocks::atlas::texture = api->texture.load("terrain.png");

	blocks::atlas::uX = 1.0 / blocks::atlas::cX;
	blocks::atlas::uY = 1.0 / blocks::atlas::cY;
	blocks::blocks.push_back(NULL);// Wind :D

	blocks::block* b = new blocks::block();

	newBlock({ 3,0 }, { 3,0 }, { 3,0 }, { 3,0 }, { 0,0 }, { 2,0 }); // Grass - 1
	newBlock({ 2,0 }, { 2,0 }, { 2,0 }, { 2,0 }, { 2,0 }, { 2,0 }); // Dirt - 2
	newBlock({ 1,0 }, { 1,0 }, { 1,0 }, { 1,0 }, { 1,0 }, { 1,0 }); // Rock - 3
	newBlock({ 13,12 }, { 13,12 }, { 13,12 }, { 13,12 }, { 13,12 }, { 13,12 }); // Water - 4
	newBlock({ 2,1 }, { 2,1 }, { 2,1 }, { 2,1 }, { 2,1 }, { 2,1 }); // Sand - 5
	newBlock({ 4,0 }, { 4,0 }, { 4,0 }, { 4,0 }, { 4,0 }, { 4,0 }); // Wood - 6
}

float *blocks::atlas::getUV(block* block, int tid)
{
	return block->tUVS[tid];
}