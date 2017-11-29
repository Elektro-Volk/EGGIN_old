#include "World.h"
#include "Chunk.h"
#include "blocks.h"

void Chunk::generate()
{
	FastNoise *noise = &((World*)parent)->noise;
	for (int x = 0; x < 16; x++)
		for (int z = 0; z < 16; z++)
		{
			float X = position.x + x;
			float Z = position.z + z;
			
			int n = noise->GetPerlin(X * 10.0f, Z * 10.0f) * 5.0f // Global
				+ noise->GetPerlin(X * 5.0f, Z * 5.0f) * 10.f
				+ noise->GetPerlin(X * 1.0f, Z * 1.0f) * 25.f
				+ noise->GetPerlin(X * 0.1f, Z * 0.1f) * 50.f;
			int top = n*(noise->GetPerlin(X * 0.05f, Z * 0.05f)/2.f+0.5f) +20;
			for (int y = 0; y < 16; y++)
				if(position.y + y <= top)
					blocks[x][z][y] = { 1 };
		}
}

void push_backs(vector<float>* m, vector<float> data)
{
	for (auto d : data)
		m->push_back(d);
}

vector<float> getUV(float x, float y, float x2, float y2)
{
	return { x, y, x2, y, x2, y2, x2, y2, x, y2, x, y };
}

int isBlock(block_data (&blocks)[16][16][16], int x, int y, int z)
{
	if (x < 0 || x >= 16)
		return 0;
	if (y < 0 || y >= 16)
		return 0;
	if (z < 0 || z >= 16)
		return 0;
	return blocks[x][z][y].bid;
}

void Chunk::build()
{
	vector<float> *verts = new vector<float>();
	vector<float> *uvs = new vector<float>();

	for (int x = 0; x<16; x++)
		for (int y = 0; y<16; y++)
			for (int z = 0; z < 16; z++)
			{
				int blockId = blocks[x][z][y].bid;
				if (!blockId)
					continue;
				
				float xp = x + 0.5f;
				float xm = x - 0.5f;
				float yp = y + 0.5f;
				float ym = y - 0.5f;
				float zp = z + 0.5f;
				float zm = z - 0.5f;

				/* FORWARD */
				if (!isBlock(blocks, x, y, z + 1)) {
					push_backs(verts, {
						xm, ym, zp, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xm, yp, zp, xm, ym, zp });
					push_backs(uvs, blocks::atlas::getUV(blockId, 0));
				}
				/* BACK */
				if (!isBlock(blocks, x, y, z - 1)) {
					push_backs(verts, {
						xm, ym, zm, xp, ym, zm,
						xp, yp, zm, xp, yp, zm,
						xm, yp, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(blockId, 1));
				}
				/* LEFT */
				if (!isBlock(blocks, x - 1, y, z)) {
					push_backs(verts, {
						xm, ym, zm, xm, ym, zp,
						xm, yp, zp, xm, yp, zp,
						xm, yp, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(blockId, 2));
				}
				/* RIGHT */
				if (!isBlock(blocks, x + 1, y, z)) {
					push_backs(verts, {
						xp, ym, zm, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xp, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(blockId, 3));
				}
				/* TOP */
				if (!isBlock(blocks, x, y + 1, z)) {
					push_backs(verts, {
						xm, yp, zm, xm, yp, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xm, yp, zm });
					push_backs(uvs, blocks::atlas::getUV(blockId, 4));
				}
				/* BOTTOM */
				if (!isBlock(blocks, x, y - 1, z)) {
					push_backs(verts, {
						xm, ym, zm, xm, ym, zp,
						xp, ym, zp, xp, ym, zp,
						xp, ym, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(blockId, 5));
				}
			}

	mesh.uvs = uvs->data();
	mesh.uv_size = uvs->size();
	mesh.vertices = verts->data();
	mesh.vert_size = verts->size() / 3;
}