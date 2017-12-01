#pragma once
#include "../EGGIN/gameobject.h"
#include "../../Libs/SDL2-2.0.5/include/SDL_keyboard.h"
#include "../EGGIN/api.h"

bool check(float Dx, float Dy, float Dz);

class Player : public GameObject
{
public:
	float dx, dy, dz;
	float w, h, d;  // width, height, depth 
	bool onGround;
	float speed;
	const float size = 1.f;

	Player(float x0, float y0, float z0)
	{
		setGlobalPosition(vec3(x0, y0, z0));
		dx = 0; dy = 0; dz = 0;
		w = 5; h = 20; d = 5; speed = 2;
		onGround = false;
	}

	

	void collision(float Dx, float Dy, float Dz)
	{
		if (check(position.x, position.y-0.1f, position.z)){
			if (dy < 0.f) { onGround = true; dy = 0; }
		}
		if ((dz > 0.f && check(position.x, position.y + 0.1f, position.z - 0.6f))
		|| (dz < 0.f && check(position.x, position.y + 0.1f, position.z + 0.6f)))
			dz = 0;
		if ((dx > 0.f && check(position.x - 0.6f, position.y + 0.1f, position.z))
			|| (dx < 0.f && check(position.x + 0.6f, position.y + 0.1f, position.z)))
			dx = 0;
	}

	void update()
	{
		keyboard();

		float time = 0.1f;
		if (!onGround) dy -= 1.5*time;
		onGround = 0;

		collision(0, dy, 0);
		position.x -= dx*time;
		position.y += dy*time;
		position.z -= dz*time;

		dx /= 2.f;
		dz /= 2.f;
		if (dx > -0.1f || dx < 0.1f)
			dx = 0;
		if (dz > -0.1f || dz < 0.1f)
			dz = 0;

		if (position.y < -10.f)
			position.y = 100.f;
	}

	

	void keyboard()
	{
		if (api->input.isKey(SDL_SCANCODE_SPACE)) if (onGround) { onGround = false; dy = 3; };
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