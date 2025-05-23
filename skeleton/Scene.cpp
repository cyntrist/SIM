#include "Scene.h"
#include "GameObject.h"

Scene::Scene(Camera* cam, PxPhysics* gPhysics, PxScene* gScene) : camera(cam), gPhysics(gPhysics), gScene(gScene)
{
	setup();
}

void Scene::setObjsVisible(bool vis)
{
	for (auto go : gameObjects)
		go.second.gameObject->setVisible(vis);
}

void Scene::addGameObject(GameObject* obj, ParticleGenerator* partGen)
{
	if (gameObjects.count(obj->getName()))
		obj->setName(obj->getName() + " (" + to_string(gameObjects.count(obj->getName())) + ")");
	ObjInfo infogb = {obj, partGen };
	Log("GAME OBJECT CREATED: " + obj->getName());
	gameObjects.insert({obj->getName(), infogb });
}

void Scene::deleteGameObject(const string& name)
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
		deleteGameObject(o);

	for (const auto s : systems)
	{
		s->update(t);
		s->affectParticles(gameObjects, t);
	}
}
