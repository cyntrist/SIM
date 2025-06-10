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
	bool levelWon = false;

public:
	SceneManager(PxPhysics* gphys, PxScene* gscn);
	~SceneManager();

	void update(float t);
	void addScene(Scene* scn);
	void setScene(int id);
	void keyPressed(unsigned char key, const PxTransform& camera);
	void specialKeyPressed(int key, const PxTransform& camera);
	void setWon(bool v) { levelWon = v; }
	bool getWon() const { return levelWon; }
};
