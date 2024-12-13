#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include "GameObject.h"
#include "Global.h"
#include "System.h"

using namespace std;
using namespace physx;

class Scene
{
protected:
	bool active = false;
	unordered_map<string, ObjInfo> gameObjects;
	vector<System*> systems;

	Camera* camera = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

public:
	Scene() { setup(); };
	virtual ~Scene() = default;

	// getters
	unordered_map<string, ObjInfo> getObjects() const { return gameObjects; }
	vector<System*> getSystems() const { return systems; }
	Camera* getCamera() const { return camera; }
	bool getActive() const { return active; }
	PxPhysics* getPxPhysics() const { return gPhysics; }
	PxScene* getPxScene() const { return gScene; }

	void show()
	{
		update(0);
		active = true;
		setObjsVisible(active);
	};

	void hide()
	{
		active = false;
		setObjsVisible(active);
	};

	void toggle()
	{
		active = !active;
		setObjsVisible(active);
	};

	void setObjsVisible(bool vis)
	{
		for (auto go : gameObjects)
			go.second.gameObject->setVisible(vis);
	}

	virtual void setup()
	{
	};

	void addObject(GameObject* obj, ParticleGenerator* partGen)
	{
		if (const int i = gameObjects.count(obj->getName()) > 0)
			obj->setName(obj->getName() + "(" + to_string(i) + ")");
		ObjInfo infogb = {obj, partGen};
		gameObjects.insert({obj->getName(), infogb});
	}

	void deleteObject(string& name)
	{
		const auto objInfo = gameObjects.find(name);

		if (objInfo == gameObjects.end())
			return;

		if (objInfo->second.partGen)
			objInfo->second.partGen = nullptr;

		delete objInfo->second.gameObject;
		gameObjects.erase(name);
	}

	void addSystem(System* sys)
	{
		systems.push_back(sys);
	}

	void update(double t)
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

	void setActorVisible(PxRigidActor* actor, bool vis)
	{
		vis ? gScene->addActor(*actor) : gScene->removeActor(*actor);
	}

	virtual void keyPressed(unsigned char key, const PxTransform& camera)
	{
	};
};
