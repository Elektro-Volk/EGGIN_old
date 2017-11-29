#include "World.h"

bool World::isColumn(int x, int z)
{
	return chunks.find(x) == chunks.end() && chunks[x].find(z) == chunks[x].end();
}

vec3 *World::FindNearestEmptyColumn(int cx, int cz, int rad)
{
	vec3 center = vec3(cx, 0, cz);
	vec3 near;
	bool isNear = false;
	for (int z = cz - rad; z <= cz + rad; z++)
	{
		for (int x = cx - rad; x <= cx + rad; x++)
		{
			vec3 current = vec3(x, 0, z);
			int dis = (int)center.distance(current);
			if (dis > rad)
				continue;
			if (isColumn(x, z))
				continue;
			if (!isNear)
			{
				isNear = true;
				near = current;
			}
			else
			{
				int oldDis = (int)center.distance(near);
				if (dis < oldDis)
					near = current;
			}
		}
	}
	return isNear ? new vec3(near) : nullptr;
}

Chunk* World::createChunk(int x, int y, int z)
{
	Chunk *c = new Chunk();
	api->gameobject.reg(c);
	c->setGlobalPosition({ x * 16.0f, y * 16.0f, z * 16.0f });
	c->generate();
	c->build();
	return c;
}

void World::buildColumn(int x, int z)
{
	if (chunks.find(x) == chunks.end())
		chunks[x] = map<int, vector<Chunk*>>();
	chunks[x][z] = vector<Chunk*>();
	vector<Chunk*>* col = &chunks[x][z];
	for (int y = 0; y < 16; y++)
		col->push_back(createChunk(x, y, z));
}

void World::tUpdate()
{
	//vec3 p = player->getGlobalPosition();
	//vec3 *t = FindNearestEmptyColumn((int)p.x / 8, (int)p.z / 8, 5);
	//if (t != nullptr)
	//	buildColumn(t->x, t->z);
	//delete t;
	//for (int x = -2; x < 2; x++)
	//	for (int z = -2; z < 2; z++)
	//		buildColumn(x, z);
}