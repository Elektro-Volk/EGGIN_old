#pragma once
#include "common.h"
#include "vec.h"



class GameObject
{
private:
	vec3 position;
	vec3 rotation;
public:
	int id;
	std::vector<GameObject*> childs;
	GameObject* parent;

	GameObject()
	{
	}

	vec3 getLocalPosition();
	vec3 getGlobalPosition();
	void setLocalPosition(vec3 position);
	void setGlobalPosition(vec3 position);

	virtual void update() {}
};

namespace gameobject
{
	extern std::map<int, GameObject*> gameobjects;

	int reg(GameObject* go);
	void unreg(GameObject* go);
}