#pragma once
#include "../EGGIN/gameobject.h"
#include "../EGGIN/api.h"

class BlockCursor : public GameObject
{
private:
	render::mesh mesh;
public:
	BlockCursor()
	{
		mesh = render::mesh();
		mesh.vertices = new float[90]{
			-0.51f, -0.51f, 0.51f,
			0.51f, -0.51f, 0.51f,
			0.51f, 0.51f, 0.51f,
			0.51f, 0.51f, 0.51f,
			-0.51f, 0.51f, 0.51f,
			-0.51f, -0.51f, 0.51f,
			//
			-0.51f, -0.51f, 0.51f,
			-0.51f, -0.51f, -0.51f,
			-0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, 0.51f,
			-0.51f, -0.51f, 0.51f,
			//
			-0.51f, -0.51f, -0.51f,
			0.51f, -0.51f, -0.51f,
			0.51f, 0.51f, -0.51f,
			0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, -0.51f,
			-0.51f, -0.51f, -0.51f,
			//
			0.51f, -0.51f, 0.51f,
			0.51f, -0.51f, -0.51f,
			0.51f, 0.51f, -0.51f,
			0.51f, 0.51f, -0.51f,
			0.51f, 0.51f, 0.51f,
			0.51f, -0.51f, 0.51f,
			//
			0.51f, 0.51f, 0.51f,
			0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, -0.51f,
			-0.51f, 0.51f, 0.51f,
			0.51f, 0.51f, 0.51f
		};
		mesh.uvs = new float[60]{
			1., 1.f,
			0., 1.f,
			0., 0.f,
			0., 0.f,
			1., 0.f,
			1., 1.f,
			//
			1., 1.f,
			0., 1.f,
			0., 0.f,
			0., 0.f,
			1., 0.f,
			1., 1.f,
			//
			1., 1.f,
			0., 1.f,
			0., 0.f,
			0., 0.f,
			1., 0.f,
			1., 1.f,
			//
			1., 1.f,
			0., 1.f,
			0., 0.f,
			0., 0.f,
			1., 0.f,
			1., 1.f,
			//
			1., 1.f,
			0., 1.f,
			0., 0.f,
			0., 0.f,
			1., 0.f,
			1., 1.f,
		};

		mesh.vert_size = 30;
		mesh.mat = api->material.create("cursor.mat");
	};

	void draw3D() override
	{
		api->render.api->mesh.draw(&this->mesh, this->getGlobalPosition(), vec3());
	}
};