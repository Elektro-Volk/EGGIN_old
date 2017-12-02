#pragma once
#include "FastNoise.h"

class WorldGenerator {
private:
	FastNoise noise;
public:
	WorldGenerator(int seed);
	void generateColumn(class Chunk** chunks);
};