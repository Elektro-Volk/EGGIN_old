#pragma once
#include "render.h"
#include "gameobject.h"
#include "common.h"

struct engineapi {
	struct {
		void(*dev)(string str);
		void(*log)(string str);
	} console;
	struct {
		void (*criticalError)(string error);
	} host;
	struct {
		render::mesh* (*load)(const char* name);
	} models;
	struct {
		void (*reg)(GameObject* go);
		void (*unreg)(GameObject* go);
	} gameobject;
	struct { 
		material*(*create)(string str);
	} material;
	struct {
		render::api_s *api;
		GameObject* camera;
	} render;
	struct {
		bool (*isKey)(int code);
		bool (*isMouseKey)(int code);
		void (*getMouseSpeed)(int &x, int &y);
	} input;
};

extern engineapi* api;