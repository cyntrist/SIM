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
	unordered_map<string, ObjInfo> gameObjects;
	vector<System*> systems;

	Camera* camera = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

public:
	Scene() { setup(); };
	Scene(Camera* cam, PxPhysics* gPhysics = nullptr, PxScene* gScene = nullptr);
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

	void addSystem(System* sys)
	{
		systems.push_back(sys);
	}

	virtual void setup()
	{
	};

	void setObjsVisible(bool vis);
	void addGameObject(GameObject* obj, ParticleGenerator* partGen = nullptr);
	void deleteGameObject(string& name);
	void update(double t);

	void setActorVisible(PxRigidActor* actor, bool vis)
	{
		vis ? gScene->addActor(*actor) : gScene->removeActor(*actor);
	}

	virtual void keyPressed(unsigned char key, const PxTransform& camera)
	{
	};
};
