#pragma once
#include "common.h"

namespace console
{
	void init();
	void dev(const char *format, ...);
	void dev(string str);
	void log(const char *format, ...);
	void log(string str);
}