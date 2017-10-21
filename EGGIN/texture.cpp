#include "console.h"
#include "host.h"
#include "SDL.h"
#include "common.h"
#include "render.h"

int texture::load(string name)
{
	SDL_Surface* textureImage = SDL_LoadBMP(("textures/"+name).c_str());
	int tid = render::rApi.texture.create(textureImage->w, textureImage->h, textureImage->pixels);
	SDL_FreeSurface(textureImage);
	return tid;
}

void texture::unload(int tid)
{
	render::rApi.texture.free(tid);
}
