#pragma once
#include <iostream>
#include <vector>
#include "SceneObject.h"

class Scene
{
protected:
	std::vector<SceneObject*> objs;
	std::vector<SceneObject*> deletables;

public:
	Scene() = default;
	~Scene() = default;

	void addObject(SceneObject* obj)
	{
		objs.push_back(obj);
	}

	void update(double t)
	{
		for (auto obj : deletables)
		{
			delete obj;
			obj = nullptr;
		}

		for (const auto obj : objs)
			obj->update(t);

		for (auto obj : objs)
			if (!obj->isAlive())
			{
				deletables.push_back(obj);
				const auto ref = std::find(objs.begin(), objs.end(), obj);
				objs.erase(ref);
			}
	}
};
