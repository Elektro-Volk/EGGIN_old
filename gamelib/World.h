#pragma once
#include "Chunk.h"
#include "FastNoise.h"
#include <map>


class World : public GameObject
{
private:
	map<int, map<int, vector<Chunk*>>> chunks;
	GameObject* player;
public:
	FastNoise noise;

	World() 
	{
		noise = FastNoise();
	}

	void setPlayer(GameObject* g) {
		player = g;
	}

	bool isColumn(int x, int z);
	vec3 *FindNearestEmptyColumn(int cx, int cz, int rad);
	Chunk* createChunk(int x, int y, int z);
	void buildColumn(int x, int z);
	void tUpdate();
};