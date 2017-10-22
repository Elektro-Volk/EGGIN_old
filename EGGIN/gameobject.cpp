#include "gameobject.h"

std::map<int, GameObject*> gameobject::gameobjects;

int gameobject::reg(GameObject* go)
{
	int i = 0;
	while (gameobject::gameobjects.find(i) != gameobject::gameobjects.end())
		i++;
	gameobject::gameobjects[i] = go;
	go->id = i;
	return i;
}

void gameobject::unreg(GameObject* go)
{
	gameobject::gameobjects.erase(go->id);
}

