#pragma once
#include "../EGGIN/gameobject.h"
#include "../../Libs/SDL2-2.0.7/include/SDL_keyboard.h"
#include "../../Libs/SDL2-2.0.7/include/SDL_mouse.h"
#include "../EGGIN/api.h"
#include "main.h"
#include "BlockCursor.hpp"

class Player : public GameObject
{
public:
	float dx, dy, dz;
	bool onGround;
	float speed;
	BlockCursor *cur;

	Player(float x0, float y0, float z0)
	{
		setGlobalPosition(vec3(x0, y0, z0));
		dx = 0; dy = 0; dz = 0;
		speed = 2;
		onGround = false;
		cur = new BlockCursor();
		api->gameobject.reg(cur);
	}



	void collision()
	{
		// Bottom
		if (dy < 0.f && thisWorld->isBlock(vec3(position.x, position.y - 0.1f, position.z))) {
			onGround = true;
			dy = 0;
		}
		
		if ((dz > 0.f && thisWorld->isBlock(vec3(position.x, position.y + 0.1f, position.z - 0.4f)))
			|| (dz < 0.f && thisWorld->isBlock(vec3(position.x, position.y + 0.1f, position.z + 0.4f))))
			dz = 0;
		if ((dx > 0.f && thisWorld->isBlock(vec3(position.x - 0.4f, position.y + 0.1f, position.z)))
			|| (dx < 0.f && thisWorld->isBlock(vec3(position.x + 0.4f, position.y + 0.1f, position.z))))
			dx = 0;
		// Top
		if (dy > 0.f && thisWorld->isBlock(vec3(position.x, position.y + 2.f, position.z))) {
			dy = 0;
		}

		if ((dz > 0.f && thisWorld->isBlock(vec3(position.x, position.y + 1.7f, position.z - 0.4f)))
			|| (dz < 0.f && thisWorld->isBlock(vec3(position.x, position.y + 1.7f, position.z + 0.4f))))
			dz = 0;
		if ((dx > 0.f && thisWorld->isBlock(vec3(position.x - 0.4f, position.y + 1.7f, position.z)))
			|| (dx < 0.f && thisWorld->isBlock(vec3(position.x + 0.4f, position.y + 1.7f, position.z))))
			dx = 0;
	}

	void update()
	{
		keyboard();

		float time = 0.1f;
		if (!onGround) dy -= 1.5*time;
		onGround = 0;

		collision();
		position.x -= dx*time;
		position.y += dy*time;
		position.z -= dz*time;

		dx = dz = 0.f;

		if (position.y < -10.f)
			position.y = 100.f;

		//api->render.api->camera.setFov(90 * (rSpeed / 2.f + 0.5f));
	}



	void keyboard()
	{
		if (onGround && api->input.isKey(SDL_SCANCODE_SPACE)) {
			onGround = false;
			dy = 3;
		}
		float spd = api->input.isKey(SDL_SCANCODE_LSHIFT) ? speed * 1.5f : speed;

		if (api->input.isKey(SDL_SCANCODE_W))
		{
			dz += -cos(rotation.y / 57.3) * spd;
			dx += sin(rotation.y / 57.3) * spd;
		}

		if (api->input.isKey(SDL_SCANCODE_S))
		{
			dz += cos(rotation.y / 57.3) * spd;
			dx += -sin(rotation.y / 57.3) * spd;
		}

		if (api->input.isKey(SDL_SCANCODE_D))
		{
			dz += -cos((rotation.y + 90) / 57.3) * spd * 0.8f;
			dx += sin((rotation.y + 90) / 57.3) * spd * 0.8f;
		}

		if (api->input.isKey(SDL_SCANCODE_A))
		{
			dz += cos((rotation.y + 90) / 57.3) * spd * 0.8f;
			dx += -sin((rotation.y + 90) / 57.3) * spd * 0.8f;
		}

		int rotX, rotY;
		api->input.getMouseSpeed(rotX, rotY);

		this->rotation.y += rotX / 5.f;
		this->rotation.x -= rotY / 5.f;
		if (this->rotation.x > 80)
			rotation.x = 80;
		if (this->rotation.x < -80)
			rotation.x = -80;


		float x = position.x;
		float y = position.y + 1.6f;
		float z = position.z;

		int X, Y, Z, oldX = 0, oldY = -1, oldZ = 0;

		for (int dist = 0; dist < 120; dist++)  // радиус действия
		{
			x -= sin(rotation.y / 57.3) / 20.; X = BP(x);
			y += tan(rotation.x / 57.3) / 20.; Y = BPY(y);
			z += cos(rotation.y / 57.3) / 20.; Z = BP(z);

			cur->setGlobalPosition(vec3(0.f, -1000.f, 0.f));
			if (thisWorld->isBlock(X, Y, Z))
			{
				cur->setGlobalPosition(vec3(X, Y, Z));
				if (api->input.isMouseKeyChanged(SDL_BUTTON_RIGHT, true))
					thisWorld->setBlock(oldX, oldY, oldZ, { 6 }, true);
				if (api->input.isMouseKeyChanged(SDL_BUTTON_LEFT, true))
					thisWorld->setBlock(X, Y, Z, { 0 }, true);
				break;
			}
			oldX = X; oldY = Y; oldZ = Z;
		}
	}
};