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

			int n = noise.GetPerlin(X * 10.0f, Z * 10.0f) * 5.0f // Global
				+ noise.GetPerlin(X * 1.0f, Z * 1.0f) * 25.f
				+ noise.GetPerlin(X * 0.1f, Z * 0.1f) * 50.f;
			int top = n*(noise.GetPerlin(X * 0.1f, Z * 0.1f) / 2.f + 0.5f) + 20;

			for (int i = 0; i < 8; i++) {
				Chunk* c = chunks[i];
				
				for (int y = 0; y < 16; y++) {
					float Y = c->position.y + y;
					if (Y <= top) {
						c->blocks[x][z][y] = { 1 };
						c->nB = false;
					}
				}
			}
		}
	}
}

