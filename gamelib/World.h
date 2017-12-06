#pragma once
#include "Chunk.h"
#include "WorldGenerator.h"
#include <map>
#include <time.h>
#define BP(x) (int)(x > 0.f ? x + 0.5f : x - 0.5f)
#define BPY(x) (int)(x < 0.f ? x + 0.5f : x - 0.5f)

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

	void loop();
public:
	World(WorldGenerator *gen, GameObject* player);

	Chunk* getChunk(int x, int y, int z);
	bool isColumn(int x, int z);
	vec3* FindNearestEmptyColumn(int cx, int cz, int rad);
	bool ClearFar(int x, int z, int rad);
	Chunk* createChunk(int x, int y, int z);
	void buildColumn(int x, int z);
	void remColumn(int x, int z);

	bool setBlock(vec3 p, block_data b, bool rebuild = false);
	bool setBlock(int x, int y, int z, block_data b, bool rebuild = false);
	block_data *getBlock(vec3 p);
	block_data *getBlock(int x, int y, int z);
	bool isBlock(vec3 p);
	bool isBlock(int x, int y, int z);

	Chunk* getLocalPos(vec3 gpos, int &_x, int &_y, int &_z);

	void draw3D() override;
};