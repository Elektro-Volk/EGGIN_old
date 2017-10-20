#pragma once

namespace render
{
	struct api_s {
		struct {
			void(*createWindow)(const char *name, int w, int h, bool fullscreen);
		} main;
	};

	extern api_s rApi;

	void init();
	void start();
	void frame();
	void shutdown();
}