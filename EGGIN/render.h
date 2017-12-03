#pragma once
#include "gameobject.h"

class material {
public:
	std::map<std::string, int> textures;
	static material* create(std::string str);
};

namespace render
{
	class mesh {
	public:
		float *vertices;
		float *uvs;
		unsigned int vert_size;
		unsigned int uv_size;
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
			void(*set2d)();
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
		struct {
			void (*set)(vec3 pos, vec3 rot);
			void(*setFov)(int fov);
		} camera;
	};

	extern api_s rApi;
	extern GameObject *camera;

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