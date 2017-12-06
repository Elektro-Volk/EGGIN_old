#include "MainMenu.h"
#include "FreeCam.hpp"
#include "menuhome.h"

eui::Button *CreateMenuButton(string image, float pos) {
	auto b = new eui::Button(
		"mmenu/"+image+".bmp",
		{ pos, -0.8f, 0.2f, 0.2f }
	);
	b->timg->setUv({ 0.0,0.0,0.5,1.0 });
	return b;
}

MainMenu::MainMenu(GameObject *camera)
{
	this->camera = camera;
	//camera->setGlobalPosition(vec3(10.f, 3.f, 11.f));
	//camera->setGlobalRotation(vec3(-10.f, -220.f, 0.f));
	//camera->parent = (new FreeCam());
	camera->setGlobalPosition(vec3(10.f, 1.5f, 10.f));// Wait for scene will build
	camera->setGlobalRotation(vec3(-90.f, 0.f, 0.f));

	c = new Chunk(0,0,0);
	createMenuHome(c->blocks);
	c->nB = false;
	c->build();

	main_buttons[0] = CreateMenuButton("play", -0.55f);
	main_buttons[1] = CreateMenuButton("multiplayer", -0.25f);
	main_buttons[2] = CreateMenuButton("settings", 0.05f);
	main_buttons[3] = CreateMenuButton("exit", 0.35f);

	api->gameobject.reg(this);
}

void MainMenu::draw2D()
{
	main_buttons[0]->draw2D();
	main_buttons[1]->draw2D();
	main_buttons[2]->draw2D();
	main_buttons[3]->draw2D();
}

void MainMenu::draw3D()
{
	c->draw3D();
}

void MainMenu::update()
{
	camera->setGlobalRotation(camera->getGlobalRotation() + vec3(0.f, 0.1f, 0.f));
}
