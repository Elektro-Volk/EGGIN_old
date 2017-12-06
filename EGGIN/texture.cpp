#include "console.h"
#include "host.h"
#include "SDL.h"
#include "common.h"
#include "render.h"
#include "SDL_image.h"

int texture::load(string name)
{
	SDL_Surface* textureImage = IMG_Load(("textures/"+name).c_str());
	int tid = render::rApi.texture.create(textureImage);
	SDL_FreeSurface(textureImage);
	return tid;
}

void texture::unload(int tid)
{
	render::rApi.texture.free(tid);
}
