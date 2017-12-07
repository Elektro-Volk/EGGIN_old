#include "World.h"
#include <thread>

void World::loop()
{
	vec3* p = &player->position;
	while (true) {
		int x = floor(p->x / 16.f);
		int z = floor(p->z / 16.f);

		u_buildNear(x, z, 3);
		u_clearFar(x, z, 4);
	}
}

World::World(WorldGenerator* gen, GameObject* player)
{
	this->gen = gen;
	this->player = player;
	this->collumns_lock = lock_new();
	thread t = thread(&World::loop, this);
	t.detach();

	api->gameobject.reg(this);
}

Chunk * World::getChunk(int x, int y, int z)
{
	lock_lock(collumns_lock);
	for (int i = 0; i < nCollumns; i++) {
		auto gs = collumns[i];
		if (x == gs[0]->X && z == gs[0]->Z) {
			lock_unlock(collumns_lock);
			return gs[y];
		}
	}
	lock_unlock(collumns_lock);
	return nullptr;
}

bool World::isColumn(int x, int z)
{
	return getChunk(x, 0, z) != nullptr;
}

void World::u_buildNear(int cx, int cz, int rad)
{
	if (!isColumn(cx, cz))
		buildColumn(cx, cz);
	vec3 center = vec3(cx, 0, cz);
	vec3 _near;
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
				_near = current;
			}
			else
			{
				int oldDis = (int)center.distance(_near);
				if (dis < oldDis)
					_near = current;
			}
		}
	}
	if(isNear)
		buildColumn(_near.x, _near.z);
}

void World::u_clearFar(int x, int z, int rad)
{
	lock_lock(collumns_lock);
	vec3 pos = vec3(x, 0.f, z);
	for (int i = 0; i < nCollumns; i++) {
		Chunk* C = collumns[i][0];
		if (pos.distance(vec3(C->X, 0.f, C->Z)) > rad) {
			remColumn(C->X, C->Z);
			break;
		}
	}
	lock_unlock(collumns_lock);
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
	Chunk** col = (Chunk **)malloc(sizeof(Chunk*) * 8);

	for (int y = 0; y < 8; y++)
		col[y] = createChunk(x, y, z);
	gen->generateColumn(col);
	for (int y = 0; y < 8; y++) {
		this_thread::yield();
		col[y]->build();
	}

	lock_lock(collumns_lock);
	if (collumns == nullptr)
		collumns = (Chunk***)malloc(sizeof(Chunk**));
	else
		collumns = (Chunk***)realloc(collumns, (nCollumns + 1) * sizeof(Chunk**));
	collumns[nCollumns] = col;
	nCollumns++;
	lock_unlock(collumns_lock);
}

void World::remColumn(int x, int z)
{
	lock_lock(collumns_lock);
	// Rebuild array
	Chunk *** newArray = (Chunk***)malloc((nCollumns - 1) * sizeof(Chunk**));
	int newI = 0;
	bool removed = false;
	for (int i = 0; i < nCollumns; i++) {
		auto gs = collumns[i];
		if (!removed && (x == gs[0]->X && z == gs[0]->Z)) {
			// Free collumn
			for (int y = 0; y < 8; y++)
				delete gs[y];
			free(gs);
			removed = true;
		}
		else {
			newArray[newI] = collumns[i];
			newI++;
		}
	}
	free(collumns);
	collumns = newArray;
	nCollumns--;
	lock_unlock(collumns_lock);
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

block_data * World::getBlock(int x, int y, int z)
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
	lock_lock(collumns_lock);
	for (int i = 0; i < nCollumns; i++) {
		// Draw collumn
		collumns[i][0]->draw3D();
		collumns[i][1]->draw3D();
		collumns[i][2]->draw3D();
		collumns[i][3]->draw3D();
		collumns[i][4]->draw3D();
		collumns[i][5]->draw3D();
		collumns[i][6]->draw3D();
		collumns[i][7]->draw3D();
	}
	lock_unlock(collumns_lock);
}
