#pragma once
#include "common.h"

struct engineapi {
	struct {
		void(*dev)(string str);
		void(*log)(string str);
	} console;
};

extern engineapi api;