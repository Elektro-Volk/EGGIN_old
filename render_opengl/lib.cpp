#include "main.h"
#include "mesh.h"
#include "texture.h"
#include "lib.h"

engineapi engine;

int EXPORT Render_Main(engineapi& api, render::api_s& render_api)
{
	engine = api;
	render_api = {
		{// main
			createWindow,
			frame
		},
		{// mesh
			mesh::create,
			mesh::close
		},
		{// texture
			texture::create,
			texture::free
		}
	};
	return 1;
}