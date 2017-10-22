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

	vec3 GameObject::getLocalPosition()
	{
		return position;
	}

	vec3 GameObject::getGlobalPosition()
	{
		return parent ? parent->getGlobalPosition() + position : position;
	}

	void GameObject::setLocalPosition(vec3 position)
	{
		this->position = position;
	}

	void GameObject::setGlobalPosition(vec3 position)
	{
		this->position = parent ? parent->getGlobalPosition() + position : position;
	}

	virtual void update() {}
};

namespace gameobject
{
	extern std::map<int, GameObject*> gameobjects;

	int reg(GameObject* go);
	void unreg(GameObject* go);
}