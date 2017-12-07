#include "World.h"
#include "Chunk.h"
#include "blocks.h"

void push_backs(float *m[], float data[], int &size, int &as, int add)
{
	if (add + size > as) {
		as += 100;
		if (size == 0)
			*m = (float *)malloc(as * sizeof(float*));
		else
			*m = (float *)realloc(*m, as * sizeof(float*));		
	}
	for (int i = 0; i < add; i++)
		(*m)[size + i] = data[i];
	size += add;
}

void push_backs_rem(float *m[], float data[], int &size, int &as, int add)
{
	push_backs(m, data, size, as, add);
	delete[] data;
}

int isBlock(block_data (&blocks)[16][16][16], int x, int y, int z)//, Chunk c[])
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
	int nVerts = 0, nUvs = 0, sVerts = 0, sUvs = 0;

	//Chunk cs[6] = {};

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
					push_backs_rem(&verts, new float[12]{
						xm, ym, zp,
						xp, ym, zp,
						xp, yp, zp,
						xm, yp, zp }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 0), nUvs, sUvs, 8);
				}
				/* BACK */
				if (!isBlock(blocks, x, y, z - 1)) {
					push_backs_rem(&verts, new float[12]{
						xm, ym, zm, xp, ym, zm,
						xp, yp, zm,
						xm, yp, zm }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 1), nUvs, sUvs, 8);
				}
				/* LEFT */
				if (!isBlock(blocks, x - 1, y, z)) {
					push_backs_rem(&verts, new float[12]{
						xm, ym, zm, xm, ym, zp,
						xm, yp, zp,
						xm, yp, zm }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 2), nUvs, sUvs, 8);
				}
				/* RIGHT */
				if (!isBlock(blocks, x + 1, y, z)) {
					push_backs_rem(&verts, new float[12]{
						xp, ym, zm, xp, ym, zp,
						xp, yp, zp,
						xp, yp, zm }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 3), nUvs, sUvs, 8);
				}
				/* TOP */
				if (!isBlock(blocks, x, y + 1, z)) {
					push_backs_rem(&verts, new float[12]{
						xm, yp, zm, xm, yp, zp,
						xp, yp, zp,
						xp, yp, zm }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 4), nUvs, sUvs, 8);
				}
				/* BOTTOM */
				if (!isBlock(blocks, x, y - 1, z)) {
					push_backs_rem(&verts, new float[12]{
						xm, ym, zm, xm, ym, zp,
						xp, ym, zp,
						xp, ym, zm }, nVerts, sVerts, 12);
					push_backs(&uvs, blocks::atlas::getUV(b, 5), nUvs, sUvs, 8);
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
