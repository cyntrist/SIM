#include "Scene.h"
#include "GameObject.h"

Scene::Scene(Camera* cam, PxPhysics* gPhysics, PxScene* gScene) : camera(cam), gPhysics(gPhysics), gScene(gScene), gameObjects()
{
}

void Scene::setObjsVisible(bool vis)
{
	for (const auto& go : gameObjects)
		go->setVisible(vis);
}

void Scene::addSystem(System* sys)
{
		systems.push_back(sys);
}

void Scene::deleteSystem(System* sys)
{
	for (int i = 0; i < systems.size(); i++)
	{
		if (systems[i] == sys)
		{
			delete systems[i];
			auto ref = find(systems.begin(), systems.end(), systems[i]);
			systems.erase(ref);
			i--;
		}
	}
}

void Scene::onEnable()
{
	active = true;
}

void Scene::onDisable()
{
	active = false;
	for (auto syst : systems)
		delete syst;
	for (auto obj : gameObjects)
		delete obj;
	systems.clear();
	gameObjects.clear();
}

void Scene::addGameObject(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void Scene::deleteDeadObjects()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isAlive())
		{
			delete gameObjects[i];
			gameObjects[i] = nullptr;
			auto ref = find(gameObjects.begin(), gameObjects.end(), gameObjects[i]);
			gameObjects.erase(ref);
			i--;
		}
	}
}


void Scene::update(double t)
{
	if (!active) return;

	for (auto ob : gameObjects)
	{
		ob->update(t);
	}

	deleteDeadObjects();

	for (const auto s : systems)
	{
		s->update(t);
		s->affectParticles(gameObjects, t);
	}
}
