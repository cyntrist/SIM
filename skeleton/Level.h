#pragma once

#include "Scene.h"
class ForceSystem;
class RigidBodySystem;
class StaticRigidBody;
class DynamicRigidBody;

class Level : public Scene
{
protected:
	RigidBodySystem* rbSys = nullptr;
	ForceSystem* fSys = nullptr;
	std::vector<DynamicRigidBody*> griddles; // vector of dynamic rigid bodies
	int cDrb = 0; // current dynamic rigid body
	double stepAngle = 0.05;
	PxVec4 sColor = { 1, 0.8f, 0.1f, 1 },
		nColor = { 0.5, 0.5, 0.5, 1 };

public:
	Level(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Scene(cam, gphys, gscn)
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
	virtual void generateBody();
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
