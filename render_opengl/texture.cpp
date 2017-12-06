#include "texture.h"
#include "GL\glew.h"

int texture::create(void* _data)
{
	SDL_Surface *data = (SDL_Surface *)_data;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	GLuint texture_format;
	if (data->format->BytesPerPixel == 4) // Alpha channel
		texture_format = data->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA;
	else
		texture_format = data->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR;

	GLuint tid;
	glGenTextures(1, &tid);

	glBindTexture(GL_TEXTURE_2D, tid);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, data->w, data->h, 0, texture_format, GL_UNSIGNED_BYTE, data->pixels);
	// Smooth
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return tid;
}

void texture::free(int tid)
{
	GLuint id = tid;
	glDeleteTextures(1, &id);
}
