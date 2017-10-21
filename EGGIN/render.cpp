#include "console.h"
#include "libwork.h"
#include "host.h"
#include "api.h"
#include "models.h"
#include "material.h"
#include "meshrenderer.h"
#include "render.h"

static lib::instance render_lib;
typedef void(*renderMain_t)(engineapi& api, render::api_s& render_api);
static renderMain_t Render_Main;
render::api_s render::rApi;

void render::init()
{
	// TODO
}

void render::start()
{
	console::dev("Loading render engine");
	if ((render_lib = lib::open("render/render_opengl.dll")) == NULL)
		host::criticalError("Unable to load the render engine");

	if ((Render_Main = (renderMain_t)lib::addr(render_lib, "Render_Main")) == NULL)
		host::criticalError("Incorrect render library");
	console::dev("...\n");

	Render_Main(api, render::rApi);
	render::rApi.main.createWindow("EGGIN", 800, 600, false);

	meshrenderer *mr = new meshrenderer();
	mr->mesh = models::load("cube.obj");
	mr->mesh->mat = new material("default.mat");
	mr->setGlobalPosition(vec3(0, 0, -50));
	gameobject::reg(mr);
}

void render::frame()
{
	// render::rApi.main.frame();
}

void render::shutdown()
{
	// TODO
}

