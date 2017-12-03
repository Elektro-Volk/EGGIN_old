#include "camera.h"
#include <cmath>
#include "api.h"
#include <GL/glew.h>     

vec3 camera::pos;
vec3 camera::rot;
int camera::fov = 90;

void camera::setCam(vec3 pos, vec3 rot)
{
	camera::pos = pos;
	camera::rot = rot;
}

void camera::setFov(int _fov)
{
	fov = _fov;
}

void camera::setup()
{
	float rad = 57.3; //Замечательно число Пи

	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();                 // Reset the model-view matrix
	gluLookAt(camera::pos.x, camera::pos.y, camera::pos.z, 
		camera::pos.x - sin(camera::rot.y / rad),
		camera::pos.y + tan(camera::rot.x / rad),
		camera::pos.z + cos(camera::rot.y / rad),
		0, 1, 0);
}