#pragma once
#include "Chunk.h"
#include "WorldGenerator.h"
#include <map>
#include <time.h>

class World : public GameObject
{
private:
	struct CL {
		struct CL* next;
		Chunk** C;
	};
	CL* chunks = nullptr;
	bool clock = false;
	GameObject* player;
	WorldGenerator *gen;
public:
	World(WorldGenerator *gen)
	{
		this->gen = gen;
	}

	void setPlayer(GameObject* g) {
		player = g;
	} 

	Chunk* getChunk(int x, int y, int z);
	bool isColumn(int x, int z);
	vec3* FindNearestEmptyColumn(int cx, int cz, int rad);
	bool ClearFar(int x, int z, int rad);
	Chunk* createChunk(int x, int y, int z);
	void buildColumn(int x, int z);
	void remColumn(int x, int z);
	void tUpdate();
	void draw3D() override;
};