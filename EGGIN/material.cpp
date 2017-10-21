#include "material.h"
#include "render.h"

material::material(std::string str)
{
	FILE * file = fopen(("materials/"+str).c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");    return;
	}

	while (1) {
		char lineHeader[128];
		// ������ ������ ������ � �����
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = ����� �����. ����������� ���� ������
				   // else : ������ ������
		if (strcmp(lineHeader, "t") == 0) {
			char tex[2][64];
			fscanf(file, "%s %s\n", &tex[0], &tex[1]);
			textures[string(tex[0])] = texture::load(tex[1]);
		}
	}
}
