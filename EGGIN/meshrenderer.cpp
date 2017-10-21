#include "meshrenderer.h"

void meshrenderer::update()
{
	render::rApi.mesh.draw(this->mesh, this->getGlobalPosition(), vec3());
}