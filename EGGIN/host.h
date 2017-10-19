#pragma once
#include "common.h"

namespace host
{
	void initEngine(int argc, char **argv);
	void frameLoop();
	void criticalError(string error);
}