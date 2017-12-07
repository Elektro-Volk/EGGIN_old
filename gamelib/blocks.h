#pragma once
#include "../EGGIN/api.h"
#include "../EGGIN/common.h"

namespace blocks
{
	struct tex
	{
		int px;
		int py;

		float ux;
		float uy;
	};

	struct block
	{
		tex texture[6];
		float** tUVS;
	};

	extern vector<block*> blocks;

	void init();

	namespace atlas
	{
		extern int texture;
		extern int cX;
		extern int cY;
		extern float uX;
		extern float uY;

		float* getUV(block* block, int tid);
	}
}