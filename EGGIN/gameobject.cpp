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
	//gameobject::gameobjects.erase(go->id);
}

