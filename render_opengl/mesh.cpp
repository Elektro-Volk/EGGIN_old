#include "GL\glew.h"
#include "mesh.h"

void mesh::draw(render::mesh* m)
{
	glColor3f(1.0f, 0.0f, 1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Set your used arrays
	glVertexPointer(3, GL_FLOAT, 0, m->vertices.data());
	//glColorPointer(4, GL_FLOAT, 0, colors->data());
	//glTexCoordPointer(2, GL_FLOAT, 0, textureCoords.data());

	// Draw your mesh
	glDrawArrays(GL_TRIANGLES, 0, m->vertices.size() / 3); // 'size' is the number of your vertices.

														 // Reset initial state
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
