#include "Scene.h"
#include "GameObject.h"

void Scene::setObjsVisible(bool vis)
{
	for (auto go : gameObjects)
		go.second.gameObject->setVisible(vis);
}

void Scene::addObject(GameObject* obj, ParticleGenerator* partGen)
{
	if (int i = gameObjects.count(obj->getName()) > 0)
		obj->setName(obj->getName() + "(" + to_string(i) + ")");
	ObjInfo infogb = {obj, partGen};
	gameObjects.insert({obj->getName(), infogb});
}

void Scene::deleteObject(string& name)
{
	const auto objInfo = gameObjects.find(name);

	if (objInfo == gameObjects.end())
		return;

	if (objInfo->second.partGen)
		objInfo->second.partGen = nullptr;

	delete objInfo->second.gameObject;
	gameObjects.erase(name);
}


void Scene::update(double t)
{
	if (!active) return;

	vector<string> deleteList;
	for (auto ob : gameObjects)
	{
		if (ob.second.gameObject == nullptr)
		{
			deleteList.push_back(ob.second.gameObject->getName());
			continue;
		}

		ob.second.gameObject->update(t);

		if (!ob.second.gameObject->isAlive())
			deleteList.push_back(ob.second.gameObject->getName());
	}

	for (auto o : deleteList)
		deleteObject(o);

	for (const auto s : systems)
	{
		s->update(t);
		s->affectParticles(gameObjects, t);
	}
}
