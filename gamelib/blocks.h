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
		vector<tex> texture;
	};

	extern vector<block*> blocks;

	void init();

	namespace atlas
	{
		extern material* mat;
		extern int cX;
		extern int cY;
		extern float uX;
		extern float uY;

		vector<float> getUV(int block, int tid);
	}
}