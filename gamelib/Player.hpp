#pragma once
#include "../EGGIN/gameobject.h"
#include "../../Libs/SDL2-2.0.7/include/SDL_keyboard.h"
#include "../EGGIN/api.h"
#include "main.h"
#include "BlockCursor.hpp"

class Player : public GameObject
{
public:
	float dx, dy, dz;
	bool onGround;
	float speed;
	float rSpeed = 1.f;
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



	void collision(float Dx, float Dy, float Dz)
	{
		if (thisWorld->isBlock(vec3(position.x, position.y - 0.1f, position.z))) {
			if (dy < 0.f) { onGround = true; dy = 0; }
		}
		if ((dz > 0.f && thisWorld->isBlock(vec3(position.x, position.y + 0.1f, position.z - 0.4f)))
			|| (dz < 0.f && thisWorld->isBlock(vec3(position.x, position.y + 0.1f, position.z + 0.4f))))
			dz = 0;
		if ((dx > 0.f && thisWorld->isBlock(vec3(position.x - 0.4f, position.y + 0.1f, position.z)))
			|| (dx < 0.f && thisWorld->isBlock(vec3(position.x + 0.4f, position.y + 0.1f, position.z))))
			dx = 0;
	}

	void update()
	{
		keyboard();

		float time = 0.1f;
		if (!onGround) dy -= 1.5*time;
		onGround = 0;

		collision(0, dy, 0);
		position.x -= dx*time*rSpeed;
		position.y += dy*time*rSpeed;
		position.z -= dz*time*rSpeed;

		dx /= 2.f;
		dz /= 2.f;
		if (dx > -0.1f || dx < 0.1f)
			dx = 0;
		if (dz > -0.1f || dz < 0.1f)
			dz = 0;
		if (onGround && dy <= 0.f && rSpeed > 1.f) {
			rSpeed -= 0.01f;
		}

		if (position.y < -10.f)
			position.y = 100.f;

		//api->render.api->camera.setFov(90 * (rSpeed / 2.f + 0.5f));
	}



	void keyboard()
	{
		if (onGround && api->input.isKey(SDL_SCANCODE_SPACE)) {
			onGround = false;
			dy = 3;
			rSpeed += 0.02f;
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

		if (api->input.isKey(SDL_SCANCODE_0))
			printf("%f %f %f\n", position.x, position.y, position.z);

		int rotX, rotY;
		api->input.getMouseSpeed(rotX, rotY);

		this->rotation.y += rotX / 5.f;
		this->rotation.x -= rotY / 5.f;
		if (this->rotation.x > 80)
			rotation.x = 80;
		if (this->rotation.x < -80)
			rotation.x = -80;

		static bool pressed;

		float x = position.x;
		float y = position.y + 0.9f;
		float z = position.z;

		int oldX, oldY, oldZ;
		oldX = x; oldY = y; oldZ = z;
		int dist = 0;
		while (dist < 20)  // радиус действия
		{
			dist++;

			x -= sin(rotation.y / 57.3) / 2.f;
			y += tan(rotation.x / 57.3) / 2.f;
			z += cos(rotation.y / 57.3) / 2.f;

			cur->setGlobalPosition(vec3(0.f, -100.f, 0.f));
			if (thisWorld->isBlock(vec3(x, y, z)))
			{
				cur->setGlobalPosition(vec3(BP(x), BPY(y), BP(z)));
				if (!pressed) {
					if (api->input.isMouseKey(1) || api->input.isMouseKey(3)) {
						if (api->input.isMouseKey(3))
							thisWorld->setBlock(vec3(oldX, oldY, oldZ), { 2 }, true);
						else
							thisWorld->setBlock(vec3(x, y, z), { 0 }, true);
					}
					pressed = true;
				}
				else
					if (!api->input.isMouseKey(1) && !api->input.isMouseKey(3))
						pressed = false;
				break;
			}

			oldX = x; oldY = y; oldZ = z;
		}
	}
};