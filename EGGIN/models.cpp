#include "models.h"

render::mesh * models::load(const char * name)
{
	FILE * file = fopen(name, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");    return false;
	}

	render::mesh* m = render::rApi.mesh.create();

	while (1) {
		char lineHeader[128];
		// читаем первый символ в файле
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = Конец файла. Заканчиваем цикл чтения
				   // else : парсим строку
		if (strcmp(lineHeader, "v") == 0) {
			float vertex[3];
			fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
			m->vertices.push_back(vertex[0]);
			m->vertices.push_back(vertex[1]);
			m->vertices.push_back(vertex[2]);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			float uv[3];
			fscanf(file, "%f %f\n", &uv[0], &uv[1]);
			m->uvs.push_back(uv[0]);
			m->uvs.push_back(uv[1]);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			//glm::vec3 normal;
			//fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			//glm::vec3 normal;
			//fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			/*std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			// По каждой вершине каждого треугольника
			for (unsigned int i = 0; i < vertexIndices.size(); i++) {
				unsigned int vertexIndex = vertexIndices[i];
				glm::vec3 vertex = temp_vertices[vertexIndex - 1];
				out_vertices.push_back(vertex);
			}*/
		}
	}
	return m;
}
