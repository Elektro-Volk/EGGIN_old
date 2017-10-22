#include "camera.h"
#include <cmath>
#include <GL/glew.h>     

vec3 camera::pos;
vec3 camera::rot;

void camera::setCam(vec3 pos, vec3 rot)
{
	camera::pos = pos;
	camera::rot = rot;
}

void camera::setup()
{
	float PI = 3.141592653; //Замечательно число Пи

	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();                 // Reset the model-view matrix
	gluLookAt(camera::pos.x, camera::pos.y, camera::pos.z, 
		camera::pos.x - sin(camera::rot.z / 180 * PI),
		camera::pos.y + (tan(camera::rot.y / 180 * PI)),
		camera::pos.z - cos(camera::rot.x / 180 * PI),
		0, 1, 0);

}