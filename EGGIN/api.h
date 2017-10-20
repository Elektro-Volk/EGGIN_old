#pragma once
#include "common.h"

struct engineapi {
	struct {
		void(*dev)(const char *format, ...);
		void(*dev)(string str);
		void(*log)(const char *format, ...);
		void(*log)(string str);
	} console;
};

extern engineapi api;