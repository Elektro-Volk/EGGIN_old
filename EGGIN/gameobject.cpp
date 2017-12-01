#include "gameobject.h"

gameobject::GoList *gameobject::gameobjects = nullptr;

void gameobject::reg(GameObject* go)
{
	GoList* E = new GoList();
	E->next = gameobjects;
	E->go = go;
	gameobjects = E;
}

void gameobject::unreg(GameObject* go)
{
	GoList* last = gameobjects;
	for (GoList* gs = gameobjects; gs != nullptr; gs = gs->next) {
		if (gs->go == go) {
			last->next = gs->next;
			delete gs;
			break;
		}
		last = gs;
	}
}

