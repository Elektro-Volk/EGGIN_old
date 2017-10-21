#pragma once

namespace texture
{
	int create (int w, int h, void* pixels);
	void free (int tid);
}