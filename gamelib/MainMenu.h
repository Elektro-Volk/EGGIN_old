#pragma once
#include "../EGGIN/gameobject.h"
#include "../EGGIN/api.h"
#include "../EGGIN/EUI_elements.h"
#include "Chunk.h"

class MainMenu : public GameObject
{
private:
	GameObject *camera;
	Chunk* c;
	// Elements
	eui::Button *main_buttons[4];
public:
	MainMenu(GameObject *camera);
	void draw2D();
	void draw3D();
	void update();
};
