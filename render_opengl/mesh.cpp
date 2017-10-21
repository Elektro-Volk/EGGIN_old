#include "GL\glew.h"
#include "mesh.h"

std::map<int, render::mesh*> mesh::meshes;

void mesh::draw(render::mesh* mesh, vec3 position, vec3 rotation)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mesh->mat->textures["main"]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, mesh->vertices.data());
	glTexCoordPointer(2, GL_FLOAT, 0, mesh->uvs.data());

	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size()/3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glTranslatef(-position.x, -position.y, -position.z);
}

render::mesh* mesh::create()
{
	render::mesh* m = new render::mesh();
	int i = 0;
	while (mesh::meshes.find(i) != mesh::meshes.end())
		i++;
	mesh::meshes[i] = m;
	m->id = i;
	return m;
}

void mesh::close(render::mesh* m)
{
	mesh::meshes.erase(m->id);
	delete m;
}