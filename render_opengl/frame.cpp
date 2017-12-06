#include "api.h"
#include "GL\glew.h"
#include "mesh.h"
#include "camera.h"
#include "frame.h"

extern GLsizei G_width;
extern GLsizei G_height;
void reshape(GLsizei width, GLsizei height);

void frames::prepare()
{
	reshape(G_width, G_height);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera::setup();
}

void frames::set2d()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
}
