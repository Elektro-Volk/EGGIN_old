#include "World.h"
#include "main.h"
#include <math.h>
#include <thread>

Chunk* World::getChunk(int x, int y, int z)
{
	while (clock)
		this_thread::yield();
	clock = true;
	for (CL* gs = chunks; gs != nullptr; gs = gs->next) {
		if (x == gs->C[0]->X && z == gs->C[0]->Z) {
			clock = false;
			return gs->C[y];
		}
	}
	clock = false;
	return nullptr;
}

bool World::isColumn(int x, int z)
{
	return getChunk(x, 0, z) != nullptr;
}

vec3* World::FindNearestEmptyColumn(int cx, int cz, int rad)
{
	if (!isColumn(cx, cz)) {
		return new vec3(cx, 0, cz);
	}
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

void  World::ClearFar(int x, int z, int rad)
{
	while (clock)
		this_thread::yield();
	clock = true;
	vec3 pos = vec3(x, 0.f, z);
	for (CL* gs = chunks; gs != nullptr; gs = gs->next)
		if (pos.distance(vec3(gs->C[0]->X, 0.f, gs->C[0]->Z)) > rad) {
			remColumn(gs->C[0]->X, gs->C[0]->Z);
			clock = false;
			return;
		}
	clock = false;
}

Chunk* World::createChunk(int x, int y, int z)
{
	Chunk *c = new Chunk(x, y, z);
	c->parent = this;
	c->setGlobalPosition({ x * 16.0f, y * 16.0f, z * 16.0f });
	return c;
}

void World::buildColumn(int x, int z)
{
	CL* E = new CL();
	E->next = chunks;
	E->C = (Chunk **)malloc(sizeof(Chunk*) * 8);
	for (int y = 0; y < 8; y++)
		E->C[y] = createChunk(x, y, z);
	gen->generateColumn(E->C);
	for (int y = 0; y < 8; y++)
		E->C[y]->build();
	chunks = E;
}

void World::remColumn(int x, int z)
{
	Chunk** c = nullptr;
	CL* last = chunks;
	for (CL* gs = chunks; gs != nullptr; gs = gs->next) {
		if (x == gs->C[0]->X && z == gs->C[0]->Z) {
			c = gs->C;

			for (int i = 0; i < 8; i++) {
				api->gameobject.unreg(c[i]);
				delete c[i];
			}
			last->next = gs->next;
			delete gs;
			break;
		}
		last = gs;
	}
}

void World::tUpdate()
{
	vec3 p = player->getGlobalPosition();
	int x = floor(p.x / 16.0f);
	int z = floor(p.z / 16.0f);

	vec3* t = FindNearestEmptyColumn(x, z, 5);
	if (t != nullptr)
		buildColumn(t->x, t->z);
	delete t;
	ClearFar(x, z, 6);
}

void World::draw3D()
{
	while (clock)
		this_thread::yield();
	clock = true;
	for (CL *E = chunks; E != nullptr; E = E->next)
		for (int i = 0; i < 8; i++)
			E->C[i]->draw3D();
	clock = false;
}
