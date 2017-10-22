#pragma once

namespace gamelib 
{
	struct api_s {
		void(*init) ();
		void(*start) ();
		void(*update) ();
	};

	extern api_s rApi;

	void init();
	void start();
}