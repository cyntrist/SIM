#pragma once
#include <iostream>
#include <vector>
#include "SceneObject.h"

class Scene
{
protected:
	std::vector<SceneObject*> objs;

public:
	Scene() = default;
	~Scene() = default;

	void addObject(SceneObject* obj)
	{
		objs.push_back(obj);
	}

	void update(double t)
	{
		for (const auto obj : objs)
			obj->update(t);
	}
};
