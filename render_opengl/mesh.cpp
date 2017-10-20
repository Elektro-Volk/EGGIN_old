#include "GL\glew.h"
#include "mesh.h"

std::map<int, render::mesh*> mesh::meshes;

void mesh::draw(render::mesh* m)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(m->pos[0], m->pos[1], m->pos[2]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, m->vertices.data());
	glTexCoordPointer(2, GL_FLOAT, 0, m->uvs.data());

	glDrawArrays(GL_TRIANGLES, 0, m->vertices.size() / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glTranslatef(-m->pos[0], -m->pos[1], -m->pos[2]);
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