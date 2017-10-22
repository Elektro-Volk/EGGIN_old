#pragma once
#include "render.h"
#include "gameobject.h"
#include "meshrenderer.h"
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
		int (*reg)(GameObject* go);
		void (*unreg)(GameObject* go);
	} gameobject;
	struct {
		material*(*create)(string str);
	} material;
};

extern engineapi api;