#include "console.h"
#include "libwork.h"
#include "host.h"
#include "api.h"

static lib::instance render_lib;
typedef void(*renderMain_t)(engineapi* api, render::api_s& render_api);
static renderMain_t Render_Main;
render::api_s render::rApi;
GameObject *render::camera;

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
	// Create camera
	camera = new GameObject();
	api->render.camera = camera;
}

void render::frame()
{
	render::rApi.camera.set(render::camera->getGlobalPosition(), render::camera->getGlobalRotation());
	render::rApi.main.preFrame();
}

void render::shutdown()
{
	// TODO
}

material *material::create(string str)
{
	FILE * file = fopen(("materials/" + str).c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");    return nullptr;
	}

	material* mat = new material();

	while (1) {
		char lineHeader[128];
		// читаем первый символ в файле
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = Конец файла. Заканчиваем цикл чтения
				   // else : парсим строку
		if (strcmp(lineHeader, "t") == 0) {
			char tex[2][64];
			fscanf(file, "%s %s\n", &tex[0], &tex[1]);
			mat->textures[string(tex[0])] = texture::load(tex[1]);
		}
	}
	return mat;
}