#pragma once
#include "../EGGIN/gameobject.h"
#include "../../Libs/SDL2-2.0.7/include/SDL_keyboard.h"
#include "../EGGIN/api.h"

class FreeCam : public GameObject
{
public:
	FreeCam()
	{
		api->gameobject.reg(this);
	}

	void update() override
	{
		if (api->input.isKey(SDL_SCANCODE_W)) {
			this->position.z += cos(rotation.y / 57.3);
			this->position.x -= sin(rotation.y / 57.3);
		}
		if (api->input.isKey(SDL_SCANCODE_S)) {
			this->position.z -= cos(rotation.y / 57.3);
			this->position.x += sin(rotation.y / 57.3);
		}

		if (api->input.isKey(SDL_SCANCODE_A)) {
			this->position.z -= cos((rotation.y + 90) / 57.3);
			this->position.x += sin((rotation.y + 90) / 57.3);
		}
		if (api->input.isKey(SDL_SCANCODE_D)) {
			this->position.z += cos((rotation.y+90) / 57.3);
			this->position.x -= sin((rotation.y + 90) / 57.3);
		}

		if (api->input.isKey(SDL_SCANCODE_SPACE))
			this->position.y += 0.1f;
		if (api->input.isKey(SDL_SCANCODE_LSHIFT))
			this->position.y -= 0.1f;

		if (api->input.isKey(SDL_SCANCODE_LEFT))
			this->rotation.y -= 1.0f;
		if (api->input.isKey(SDL_SCANCODE_RIGHT))
			this->rotation.y += 1.0f;

		if (api->input.isKey(SDL_SCANCODE_UP))
			this->rotation.x += 1.0f;
		if (api->input.isKey(SDL_SCANCODE_DOWN))
			this->rotation.x -= 1.0f;
	}
	};