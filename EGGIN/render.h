#pragma once
#include <vector>

namespace render
{
	class mesh {
	public:
		std::vector<float> vertices;
		bool VBO;

		void build();
	};

	struct api_s {
		struct {
			void(*createWindow)(const char *name, int w, int h, bool fullscreen);
			void (*frame)();
		} main;
	};

	extern api_s rApi;

	void init();
	void start();
	void frame();
	void shutdown();
}