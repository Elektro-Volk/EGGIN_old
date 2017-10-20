#pragma once
#include <map>
#include "api.h"

namespace mesh
{
	extern std::map<int, render::mesh*> meshes;

	void draw(render::mesh* m);
	render::mesh* create();
	void close(render::mesh* m);
}