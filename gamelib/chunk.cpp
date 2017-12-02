#include "World.h"
#include "Chunk.h"
#include "blocks.h"


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

	for (int x = 0; x < 16; x++) {
		float xp = x + 0.5f;
		float xm = x - 0.5f;
		for (int y = 0; y < 16; y++) {
			float yp = y + 0.5f;
			float ym = y - 0.5f;
			for (int z = 0; z < 16; z++)
			{
				int blockId = blocks[x][z][y].bid;
				if (!blockId)
					continue;

				float zp = z + 0.5f;
				float zm = z - 0.5f;

				blocks::block* b = blocks::blocks[blockId];

				/* FORWARD */
				if (!isBlock(blocks, x, y, z + 1)) {
					push_backs(verts, {
						xm, ym, zp, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xm, yp, zp, xm, ym, zp });
					push_backs(uvs, blocks::atlas::getUV(b, 0));
				}
				/* BACK */
				if (!isBlock(blocks, x, y, z - 1)) {
					push_backs(verts, {
						xm, ym, zm, xp, ym, zm,
						xp, yp, zm, xp, yp, zm,
						xm, yp, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(b, 1));
				}
				/* LEFT */
				if (!isBlock(blocks, x - 1, y, z)) {
					push_backs(verts, {
						xm, ym, zm, xm, ym, zp,
						xm, yp, zp, xm, yp, zp,
						xm, yp, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(b, 2));
				}
				/* RIGHT */
				if (!isBlock(blocks, x + 1, y, z)) {
					push_backs(verts, {
						xp, ym, zm, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xp, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(b, 3));
				}
				/* TOP */
				if (!isBlock(blocks, x, y + 1, z)) {
					push_backs(verts, {
						xm, yp, zm, xm, yp, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xm, yp, zm });
					push_backs(uvs, blocks::atlas::getUV(b, 4));
				}
				/* BOTTOM */
				if (!isBlock(blocks, x, y - 1, z)) {
					push_backs(verts, {
						xm, ym, zm, xm, ym, zp,
						xp, ym, zp, xp, ym, zp,
						xp, ym, zm, xm, ym, zm });
					push_backs(uvs, blocks::atlas::getUV(b, 5));
				}
			}
		}
	}

	mesh.vert_size = verts->size() / 3;
	mesh.uv_size = uvs->size();

	mesh.uvs = (float*)malloc(sizeof(float) * uvs->size());
	memcpy(mesh.uvs, uvs->data(), sizeof(float) * uvs->size());
	
	mesh.vertices = (float*)malloc(sizeof(float) * verts->size());
	memcpy(mesh.vertices, verts->data(), sizeof(float) * verts->size());

	delete verts, uvs;
}

block_data * Chunk::getBlock(int x, int y, int z)
{
	return &blocks[x][z][y];
}
