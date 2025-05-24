#pragma once
#include <PxPhysics.h>

#include "ParticleScene.h"

#include <vector>
class Scene;
using namespace std;
using namespace physx;

class SceneManager
{
	vector<Scene*> scenes;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;
	int actualScene = 0;

public:
	SceneManager(PxPhysics* gphys, PxScene* gscn);
	~SceneManager();

	void update(float t);
	void addScene(Scene* scn);
	void setScene(int id);
	void keyPressed(unsigned char key, const PxTransform& camera);
};
