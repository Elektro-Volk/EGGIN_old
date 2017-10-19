#include <stdio.h>
#include <stdarg.h>
#include "common.h"
#include "console.h"

void console::init()
{
	FILE *file = fopen("engine.log", "w");
	fclose(file);// Create and close Log File
	console::log("==================================================\n");
	console::log("     EGGIN " + _VERSION + "\n");
	console::log("     Copyright (C) 2017 Elektro-volk\n");
	console::log("==================================================\n");
}

void console::log(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	char text[2048];
	sprintf(text, format, args);
	console::log(string(text));
	va_end(args);
}

void console::log(string str)
{
	if (FILE *file = fopen("engine.log", "a")) {
		fprintf(file, str.c_str());
		fclose(file);
	}
}

void console::dev(const char *format, ...)
{
	if (!isDev)
		return;
	va_list args;
	va_start(args, format);
	char text[2048];
	sprintf(text, format, args);
	console::log(string(text));
	va_end(args);
}

void console::dev(string str)
{
	if (!isDev)
		return;
	console::log(str);
}