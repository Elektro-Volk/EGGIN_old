#pragma once

class vec3
{
public:
	float x;
	float y;
	float z;

	vec3()
	{
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
};