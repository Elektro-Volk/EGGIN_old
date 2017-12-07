#include "GL\glew.h"
#include "mesh.h"

std::map<int, render::mesh*> mesh::meshes;

void mesh::draw(render::mesh* mesh, vec3 position, vec3 rotation)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(position.x, position.y, position.z);
	// Rotation
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	//
	glBindTexture(
		GL_TEXTURE_2D,
		mesh->texture == -1 ? mesh->mat->textures["main"] : mesh->texture
	);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, mesh->uvs);

	glDrawArrays(mesh->rtype == 0 ? GL_TRIANGLES : GL_QUADS, 0, mesh->vert_size);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	// Rotation
	glRotatef(-rotation.x, 1, 0, 0);
	glRotatef(-rotation.y, 0, 1, 0);
	glRotatef(-rotation.z, 0, 0, 1);
	//
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