#include "gameobject.h"
#include "lock.h"

GameObject** gameobject::gameobjects = nullptr;
int gameobject::nGos = 0;
LSECT golist_lock = lock_new();

void gameobject::reg(GameObject* go)
{
	lock_lock(golist_lock);
	if (gameobjects == nullptr)
		gameobjects = (GameObject**)malloc(sizeof(GameObject*));
	else
		gameobjects = (GameObject**)realloc(gameobjects, (nGos + 1) * sizeof(GameObject*));
	gameobjects[nGos] = go;
	nGos++;
	lock_unlock(golist_lock);
}

void gameobject::unreg(GameObject* go)
{
	lock_lock(golist_lock);
	GameObject **newArray = (GameObject**)malloc((nGos - 1) * sizeof(GameObject*));
	int newI = 0;
	for (int i = 0; i < nGos; i++) 
		if(gameobjects[i] != go){
			newArray[newI] = go;
			newI++;
		}
 	free(gameobjects);
	gameobjects = newArray;
	nGos--;
	lock_unlock(golist_lock);
}

void gameobject::call(void(GameObject::*F)())
{
	lock_lock(golist_lock);
	//if (gameobjects != nullptr) {
		for (int i = 0; i < nGos; i++) {
			(gameobjects[i]->*F)();
		}
	//}
	lock_unlock(golist_lock);
}

