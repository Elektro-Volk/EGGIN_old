#include "World.h"
#include <thread>

void World::loop()
{
	vec3 *p = &player->position;
	while (true) {
		int x = floor(p->x / 16.f);
		int z = floor(p->z / 16.f);

		vec3* t = FindNearestEmptyColumn(x, z, 3);
		if (t != nullptr)
			buildColumn(t->x, t->z);
		delete t;
		this_thread::sleep_for(chrono::milliseconds(5));

		ClearFar(x, z, 4);
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

World::World(WorldGenerator * gen, GameObject* player)
{
	this->gen = gen;
	this->player = player;

	thread t = thread(&World::loop, this);
	t.detach();

	api->gameobject.reg(this);
}

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

bool World::ClearFar(int x, int z, int rad)
{
	while (clock)
		this_thread::yield();
	clock = true;
	vec3 pos = vec3(x, 0.f, z);
	for (CL* gs = chunks; gs != nullptr; gs = gs->next)
		if (pos.distance(vec3(gs->C[0]->X, 0.f, gs->C[0]->Z)) > rad) {
			remColumn(gs->C[0]->X, gs->C[0]->Z);
			clock = false;
			return true;
		}
	clock = false;
	return false;
}

Chunk * World::createChunk(int x, int y, int z)
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
	for (int y = 0; y < 8; y++) {
		this_thread::sleep_for(chrono::milliseconds(1));
		E->C[y]->build();
	}
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
				delete c[i];
			}
			last->next = gs->next;
			delete gs;
			break;
		}
		last = gs;
	}
}

bool World::setBlock(int x, int y, int z, block_data b, bool rebuild)
{
	int _x, _y, _z;
	if (Chunk* chunk = this->getLocalPos(vec3(x, y, z), _x, _y, _z)) {
		chunk->blocks[_x][_z][_y] = b;
		if (rebuild)
			chunk->build();
		return true;
	}
	return false;
}

block_data* World::getBlock(int x, int y, int z)
{
	int _x,_y,_z;
	if (Chunk* chunk = this->getLocalPos(vec3(x, y, z), _x, _y, _z)) {
		return &chunk->blocks[_x][_z][_y];
	}
	return nullptr;
}

bool World::isBlock(int x, int y, int z)
{
	block_data *b = getBlock(x,y,z);
	return b && b->bid != 0;
}
//
bool World::setBlock(vec3 p, block_data b, bool rebuild)
{
	return setBlock(BP(p.x), BPY(p.y), BP(p.z), b, rebuild);
}

block_data * World::getBlock(vec3 p)
{
	return getBlock(BP(p.x), BPY(p.y), BP(p.z));
}

bool World::isBlock(vec3 p)
{
	return isBlock(BP(p.x), BPY(p.y), BP(p.z));
}
//

Chunk * World::getLocalPos(vec3 gpos, int &x, int &y, int &z)
{
	vec3 p(floor(gpos.x / 16.f), floor(gpos.y / 16.f), floor(gpos.z / 16.f));
	if (p.y < 0 || p.y > 7)
		return nullptr;
	if (auto C = getChunk(p.x, p.y, p.z))
	{
		x = floor(gpos.x - p.x * 16);
		y = floor(gpos.y - p.y * 16);
		z = floor(gpos.z - p.z * 16);
		return C;
	}
	return nullptr;
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
