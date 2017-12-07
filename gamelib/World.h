#pragma once
#include "Chunk.h"
#include "WorldGenerator.h"
#include "../EGGIN/lock.h"

#define BP(x) (int)(x > 0.f ? x + 0.5f : x - 0.5f)
#define BPY(x) (int)(x < 0.f ? x + 0.5f : x - 0.5f)

class World : public GameObject
{
private:
	Chunk*** collumns = nullptr;
	int nCollumns = 0;
	LSECT collumns_lock;
	GameObject* player;
	WorldGenerator *gen;
	
	void loop();
	void u_buildNear(int cx, int cz, int rad);
	void u_clearFar(int x, int z, int rad);
public:
	World(WorldGenerator *gen, GameObject* player);

	Chunk* getChunk(int x, int y, int z);
	bool isColumn(int x, int z);
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