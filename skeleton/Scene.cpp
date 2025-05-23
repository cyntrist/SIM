#include "Scene.h"
#include "GameObject.h"

Scene::Scene(Camera* cam, PxPhysics* gPhysics, PxScene* gScene) : camera(cam), gPhysics(gPhysics), gScene(gScene), gameObjects()
{
	setup();
}

void Scene::setObjsVisible(bool vis)
{
	for (const auto& go : gameObjects)
		go->setVisible(vis);
}

void Scene::addGameObject(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void Scene::deleteGameObjects()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isAlive())
		{
			delete gameObjects[i];
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

	for (const auto s : systems)
	{
		s->update(t);
		s->affectParticles(gameObjects, t);
	}
}
