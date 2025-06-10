#pragma once

#include "Scene.h"
class SceneManager;
class Receiver;
class ForceSystem;
class RigidBodySystem;
class StaticRigidBody;
class DynamicRigidBody;

class Level : public Scene
{
protected:
	SceneManager* sm = nullptr;
	RigidBodySystem* rbSys = nullptr;
	ForceSystem* fSys = nullptr;
	std::vector<DynamicRigidBody*> griddles; // vector of dynamic rigid bodies
	int cDrb = 0; // current dynamic rigid body
	double stepAngle = 0.05;
	PxVec4 nColor = { 0.1, 0.8f, 0.3f, 1 },
		sColor = { 0.2, 0.8, 0.5, 1 };
	RenderItem* water = nullptr;
	Receiver* receiver = nullptr;
	double counter = 0, timer = 1000;
	bool won = false;
public:
	Level(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr, SceneManager* sm = nullptr)
	: Scene(cam, gphys, gscn), sm(sm)
	{
		lowerThreshold = 150;
		upperThreshold = 100;
	}
	~Level() override;

	void setup() override {}
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
	void specialKeyPressed(int key, const PxTransform& camera) override;
	virtual void setGriddles();
	virtual void setSystems();
	virtual void setReceiver();
	void update(double t) override;
};

class Level2 : public Level
{
public:
	Level2(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Level(gphys, gscn, cam)
	{
		
	}
	~Level2()override;
	void onEnable() override;
	void onDisable() override;
	void setGriddles() override;
	void setSystems() override;
	void update(double t) override;
	void specialKeyPressed(int key, const PxTransform& camera) override;
};
