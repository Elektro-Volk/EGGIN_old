#pragma once
#include "gameobject.h"
#include "render.h"
#include "api.h"

class meshrenderer : public GameObject
{
public:
	meshrenderer()
	{
	}

	render::mesh *mesh;
	void draw3D() override
	{
		api->render.api->mesh.draw(this->mesh, this->getGlobalPosition(), vec3());
	}
};