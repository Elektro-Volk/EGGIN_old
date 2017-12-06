#pragma once
#include "Chunk.h"

void createMenuHome(block_data bd[16][16][16]) {
	// Grass
	for (int x = 0; x < 16; x++)
		for (int z = 0; z < 16; z++)
			bd[x][z][0] = { 1 };

	// Wall 1
	for (int x = 1; x < 10; x++)
		for (int y = 1; y < 7; y++)
			bd[x][1][y] = { 6 };

	// Wall 2
	for (int z = 2; z < 9; z++)
		for (int y = 1; y < 7; y++)
			bd[1][z][y] = { 6 };

	// Wall 3
	for (int x = 6; x <= 9; x++)
		for (int y = 1; y < 7; y++)
			bd[x][5][y] = { 6 };

	// Wall 4
	for (int x = 1; x <= 6; x++)
		for (int y = 1; y < 7; y++)
			bd[x][8][y] = { 6 };

	// Wall 5
	for (int z = 6; z <= 8; z++)
		for (int y = 1; y < 7; y++)
			bd[7][z][y] = { 6 };

	// Wall 6
	for (int z = 2; z < 6; z++)
		for (int y = 1; y < 7; y++)
			bd[9][z][y] = { 6 };
}