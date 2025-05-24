#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Global.h"
#include "System.h"

using namespace std;
using namespace physx;

class GameObject;

class Scene
{
protected:
	bool active = false;
	vector<System*> systems;
	vector<GameObject*> gameObjects;

	Camera* camera = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

public:
	Scene()												{ setup(); }
	Scene(Camera* cam, PxPhysics* gPhysics = nullptr, PxScene* gScene = nullptr);
	virtual ~Scene() = default;

	// getters
	vector<GameObject*> getObjects() const				{ return gameObjects; }
	vector<System*> getSystems() const					{ return systems; }
	Camera* getCamera() const							{ return camera; }
	bool getActive() const								{ return active; }
	PxPhysics* getPxPhysics() const						{ return gPhysics; }
	PxScene* getPxScene() const							{ return gScene; }

	void show(bool s = true)
	{
		if (s) update(0);
		active = s;
		setObjsVisible(s);
	}

	void toggle()
	{
		active = !active;
		setObjsVisible(active);
	}

	void addSystem(System* sys)
	{
		systems.push_back(sys);
	}

	virtual void setup() {}
	virtual void onEnable() {}
	virtual void onDisable() {}

	void setObjsVisible(bool vis);
	void addGameObject(GameObject* obj);
	void deleteGameObjects();
	void update(double t);

	void setActorVisible(PxRigidActor* actor, bool vis) const
	{
		vis ? gScene->addActor(*actor) : gScene->removeActor(*actor);
	}

	virtual void keyPressed(unsigned char key, const PxTransform& camera) { }
};
