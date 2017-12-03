#pragma once
#include "../EGGIN/vec.h"

namespace camera
{
	extern int fov;
	extern vec3 pos;
	extern vec3 rot;

	void setCam(vec3 pos, vec3 rot);
	void setFov(int fov);
	void setup();
}