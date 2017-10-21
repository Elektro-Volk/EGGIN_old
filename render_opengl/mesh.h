#pragma once
#include <map>
#include "../EGGIN/vec.h"
#include "api.h"

namespace mesh
{
	extern std::map<int, render::mesh*> meshes;

	void draw(render::mesh* mesh, vec3 position, vec3 rotation);
	render::mesh* create();
	void close(render::mesh* m);
}