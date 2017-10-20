#include "api.h"
#include "GL\glew.h"
#include "frame.h"

void frames::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float fogColor[4] = { 0.5f,0.8f,1.0f,1.0f };
	// Сероватый фон
	glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
}