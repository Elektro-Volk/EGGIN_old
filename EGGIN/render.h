#pragma once
#include "common.h"
#include <vector>
#include <map>

class material {
public:
	std::map<std::string, int> textures;
	material(std::string str);
};

namespace render
{
	class mesh {
	public:
		float pos[3];
		float rot[3];
		std::vector<float> vertices;
		std::vector<float> uvs;
		unsigned int vsize;
		material* mat;
		bool VBO;
		int id;
		
		void build();
	};

	struct api_s {
		struct {
			void(*createWindow)(const char *name, int w, int h, bool fullscreen);
			void (*frame)();
		} main;
		struct {
			render::mesh* (*create)();
			void (*close)(render::mesh* m);
		} mesh;
		struct {
			int(*create)(int w, int h, void* pixels);
			void(*free)(int tid);
		} texture;
	};

	extern api_s rApi;

	void init();
	void start();
	void frame();
	void shutdown();
}

namespace texture
{
	int load(string name);
	void unload(int tid);
}