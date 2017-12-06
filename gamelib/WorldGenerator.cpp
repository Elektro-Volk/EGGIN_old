#include "WorldGenerator.h"
#include "Chunk.h"

WorldGenerator::WorldGenerator(int seed)
{
	noise = FastNoise(seed);
}

void WorldGenerator::generateColumn(Chunk ** chunks)
{
	vec3 pos = chunks[0]->position;
	for (int x = 0; x < 16; x++) {
		float X = pos.x + x;
		for (int z = 0; z < 16; z++)
		{
			float Z = pos.z + z;

			int n = noise.GetPerlin(X * 10.0f, Z * 10.0f) * 10.0f // Global
				+ noise.GetPerlin(X * 1.0f, Z * 1.0f) * 50.f
				+ noise.GetPerlin(X * 0.1f, Z * 0.1f) * 150.f;
			int top = n*noise.GetSimplex(X * 0.1f, Z * 0.1f) + 32;

			for (int i = 0; i < 8; i++) {
				Chunk* c = chunks[i];
				
				for (int y = 0; y < 16; y++) {
					float Y = c->position.y + y;
					if (Y <= top) {
						int r = top - Y;
						short bid = 1;
						// Get block
						if (r > 5)
							bid = 3;// Rock
						else if (r > 1)
							bid = 2;// Dirt
						else if (Y < 33)
							bid = 5;// Sand

						c->blocks[x][z][y] = { bid };
						c->nB = false;
					}else if(Y<32)
						c->blocks[x][z][y] = { 4 }; // Water
				}
			}
		}
	}
}

