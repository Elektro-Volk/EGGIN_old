#include "libwork.h"

lib l;
int(*Host_Main)(int argc, char **argv);

void loadLib()
{
	l = openlib("EGGIN.dll");
	Host_Main = (int(*)(int, char **))getaddr(l, "Host_Main");
}

int main(int argc, char **argv)
{
	loadLib();
	return Host_Main(argc, argv);
}