#pragma once
#include "../EGGIN/gameobject.h"
#include "../../Libs/SDL2-2.0.5/include/SDL_keyboard.h"
#include "../EGGIN/api.h"

class Skybox : public GameObject
{
private:
	render::mesh mesh;
public:
	Skybox()
	{
		mesh = render::mesh();
		vector<float> verts = {
			-100, -100, 100,
			100, -100, 100,
			100, 100, 100,
			100, 100, 100,
			-100, 100, 100,
			-100, -100, 100,
			//
			-100, -100, 100,
			-100, -100, -100,
			-100, 100, -100,
			-100, 100, -100,
			-100, 100, 100,
			-100, -100, 100,
			//
			-100, -100, -100,
			100, -100, -100,
			100, 100, -100,
			100, 100, -100,
			-100, 100, -100,
			-100, -100, -100,
			//
			100, -100, 100,
			100, -100, -100,
			100, 100, -100,
			100, 100, -100,
			100, 100, 100,
			100, -100, 100,
			//
			100, 100, 100,
			100, 100, -100,
			-100, 100, -100,
			-100, 100, -100,
			-100, 100, 100,
			100, 100, 100
		};
		vector<float> uvs = {
			0.25, 0.66666f,
			0.0, 0.66666f,
			0.0, 0.33333f,
			0.0, 0.33333f,
			0.25, 0.33333f,
			0.25, 0.66666f,
			//
			0.25, 0.66666f,
			0.5f, 0.66666f,
			0.5f, 0.33333f,
			0.5f, 0.33333f,
			0.25, 0.33333f,
			0.25, 0.66666f,
			//
			0.5, 0.66666f,
			0.75f, 0.66666f,
			0.75f, 0.33333f,
			0.75f, 0.33333f,
			0.5, 0.33333f,
			0.5, 0.66666f,
			//
			1.0, 0.66666f,
			0.75f, 0.66666f,
			0.75f, 0.33333f,
			0.75f, 0.33333f,
			1.0, 0.33333f,
			1.0, 0.66666f,
			//
			0.25, 0.0f,
			0.5, 0.0f,
			0.5, 0.33333f,
			0.5, 0.33333f,
			0.25, 0.33333f,
			0.25, 0.0f,
		};

		mesh.uvs = uvs.data();
		mesh.vertices = verts.data();
		mesh.vert_size = verts.size() / 3;
		mesh.uv_size = uvs.size();
		mesh.mat = api->material.create("sky_day.mat");
		parent = api->render.camera;
	};

	void draw3D() override
	{
		api->render.api->mesh.draw(&this->mesh, this->getGlobalPosition(), vec3());
	}
};