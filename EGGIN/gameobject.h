#pragma once
#include "common.h"
#include "vec.h"

class GameObject
{
public:
	vec3 position;
	vec3 rotation;
	
	std::vector<GameObject*> childs;
	GameObject* parent;
	int id;

	GameObject()
	{
	}

	virtual vec3 GameObject::getLocalPosition()
	{
		return position;
	}

	virtual vec3 GameObject::getGlobalPosition()
	{
		return parent ? parent->getGlobalPosition() + position : position;
	}

	virtual void GameObject::setLocalPosition(vec3 position)
	{
		this->position = position;
	}

	virtual void GameObject::setGlobalPosition(vec3 position)
	{
		this->position = parent ? parent->getGlobalPosition() + position : position;
	}

	virtual vec3 GameObject::getLocalRotation()
	{
		return rotation;
	}

	virtual vec3 GameObject::getGlobalRotation()
	{
		return parent ? parent->getGlobalRotation() + rotation : rotation;
	}

	virtual void GameObject::setLocalRotation(vec3 rotation)
	{
		this->rotation = rotation;
	}

	virtual void GameObject::setGlobalRotation(vec3 rotation)
	{
		this->rotation = parent ? parent->getGlobalPosition() + rotation : rotation;
	}

	virtual void update() {}
	virtual void draw3D() {}
	virtual void draw2D() {}
};

namespace gameobject
{
	struct GoList {
		GameObject* go;
		struct GoList* next;
	};
	extern GoList *gameobjects;



	void reg(GameObject* go);
	void unreg(GameObject* go);
}