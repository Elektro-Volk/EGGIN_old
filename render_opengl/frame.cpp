#include "api.h"
#include "GL\glew.h"
#include "mesh.h"
#include "frame.h"

render::mesh* m = new render::mesh();

void frames::draw()
{
	m->vertices = {
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		0.5f,1.0f,0.0f
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float fogColor[4] = { 1.0f,0.1f,0.0f,1.0f };
	// Сероватый фон
	glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);

	mesh::draw(m);
}