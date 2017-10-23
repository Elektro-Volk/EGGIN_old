#include "texture.h"
#include "GL\glew.h"

int texture::create(int w, int h, void * pixels)
{
	GLuint tid;
	glGenTextures(1, &tid);

	//Typical texture generation using data from the bitmap.
	glBindTexture(GL_TEXTURE_2D, tid);

	//Generate the texture.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	//Linear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	return tid;
}

void texture::free(int tid)
{
	GLuint id = tid;
	glDeleteTextures(1, &id);
}
