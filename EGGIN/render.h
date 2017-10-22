#pragma once
#include "common.h"
#include "vec.h"

class material {
public:
	std::map<std::string, int> textures;
	static material* create(std::string str);
};

namespace render
{
	class mesh {
	public:
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
			void (*preFrame)();
			void(*postFrame)();
		} main;
		struct {
			render::mesh* (*create)();
			void (*close)(render::mesh* m);
			void(*draw)(render::mesh* mesh, vec3 position, vec3 rotation);
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