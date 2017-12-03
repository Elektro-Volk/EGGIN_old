#include "World.h"
#include "Chunk.h"
#include "blocks.h"
#include <array>

void push_backs(float *m[], float data[], int &size, int add)
{
	if (size == 0)
		*m = (float *)malloc(add * sizeof(float*));
	else
		*m = (float *)realloc(*m, (size + add) * sizeof(float*));
	for (int i = 0; i < add; i++)
		(*m)[size + i] = data[i];
	size += add;
	delete[] data;
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
	if (nB) return; // NULL CHUNK
	float* verts = nullptr, *uvs = nullptr;
	int nVerts = 0, nUvs = 0;

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
					push_backs(&verts, new float[18]{
						xm, ym, zp, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xm, yp, zp, xm, ym, zp }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 0), nUvs, 12);
				}
				/* BACK */
				if (!isBlock(blocks, x, y, z - 1)) {
					push_backs(&verts, new float[18]{
						xm, ym, zm, xp, ym, zm,
						xp, yp, zm, xp, yp, zm,
						xm, yp, zm, xm, ym, zm }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 1), nUvs, 12);
				}
				/* LEFT */
				if (!isBlock(blocks, x - 1, y, z)) {
					push_backs(&verts, new float[18]{
						xm, ym, zm, xm, ym, zp,
						xm, yp, zp, xm, yp, zp,
						xm, yp, zm, xm, ym, zm }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 2), nUvs, 12);
				}
				/* RIGHT */
				if (!isBlock(blocks, x + 1, y, z)) {
					push_backs(&verts, new float[18]{
						xp, ym, zm, xp, ym, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xp, ym, zm }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 3), nUvs, 12);
				}
				/* TOP */
				if (!isBlock(blocks, x, y + 1, z)) {
					push_backs(&verts, new float[18]{
						xm, yp, zm, xm, yp, zp,
						xp, yp, zp, xp, yp, zp,
						xp, yp, zm, xm, yp, zm }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 4), nUvs, 12);
				}
				/* BOTTOM */
				if (!isBlock(blocks, x, y - 1, z)) {
					push_backs(&verts, new float[18]{
						xm, ym, zm, xm, ym, zp,
						xp, ym, zp, xp, ym, zp,
						xp, ym, zm, xm, ym, zm }, nVerts, 18);
					push_backs(&uvs, blocks::atlas::getUV(b, 5), nUvs, 12);
				}
			}
		}
	}

	mesh.vert_size = nVerts / 3;
	mesh.uv_size = nUvs;

	mesh.uvs = uvs;
	mesh.vertices = verts;
}

block_data * Chunk::getBlock(int x, int y, int z)
{
	return &blocks[x][z][y];
}
