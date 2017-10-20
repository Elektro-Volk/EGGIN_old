#pragma once
#include <vector>

namespace render
{
	class mesh {
	public:
		float pos[3];
		float rot[3];
		std::vector<float> vertices;
		std::vector<float> uvs;
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
	};

	extern api_s rApi;

	void init();
	void start();
	void frame();
	void shutdown();
}