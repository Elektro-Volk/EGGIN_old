#pragma once
#include "gameobject.h"
#include "render.h"

class meshrenderer : public GameObject
{
public:
	meshrenderer()
	{
	}

	render::mesh *mesh;
	void update() override;
};