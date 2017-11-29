#pragma once
#include "gameobject.h"

namespace gameobjects {
	// Events
	struct eList {
		GameObject* go;
		struct eList* next;
	};
	template<class GO>
	extern eList* list;

	void call(void(*_F)(GO *go));
	void update(GO *go);
	void regGO(GO *go);
};