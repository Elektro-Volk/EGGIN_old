#include "main.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "frame.h"
#include "lib.h"

engineapi* api;

int EXPORT Render_Main(engineapi* _api, render::api_s& render_api)
{
	api = _api;
	render_api = {
		{// main
			createWindow,
			preFrame,
			postFrame,
			frames::set2d
		},
		{// mesh
			mesh::create,
			mesh::close,
			mesh::draw
		},
		{// texture
			texture::create,
			texture::free
		},
		{// camera
			camera::setCam
		}
	};
	return 1;
}