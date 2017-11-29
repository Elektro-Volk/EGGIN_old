#include "gameobjects.h"

template<class GO>
gameobjects::eList* gameobjects::list_update;

template<class GO>
void gameobjects::call(void(*F)(GO*))
{
	for(eList* element = list; element != nullptr; element = element->next)
	{
		// Fucking member-function pointer
		F(element->go);
	}
}

template<class GO>
void gameobjects::regGO(GO* go)
{
	eList *element = new eList();
	element->next = list;
	element->go = go;
	list = element;
}

void gameobjects::update(GO * go)
{
	go->update();
}
