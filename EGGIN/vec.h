#pragma once
#include <math.h>

class vec3
{
public:
	float x;
	float y;
	float z;

	vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3 operator+(vec3 _Right)
	{
		return { x + _Right.x, y + _Right.y, z + _Right.z };
	}

	float distance(vec3 _Right)
	{
		return sqrt(pow(x - _Right.x, 2) + pow(y - _Right.y, 2) + pow(z - _Right.z, 2));
	}
};