#pragma once

#include "Scene.h"
class RigidBodySystem;
class StaticRigidBody;
class DynamicRigidBody;

class Level : public Scene
{
	RigidBodySystem* system = nullptr;
	std::vector<DynamicRigidBody*> drbs; // vector of dynamic rigid bodies
	int cDrb = 0; // current dynamic rigid body
	double stepAngle = 0.05;
	PxVec4 sColor = { 1, 0.8f, 0.1f, 1 },
		nColor = { 0.5, 0.5, 0.5, 1 };

public:
	Level(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Scene(cam, gphys, gscn) {}
	~Level() override;

	void setup() override {}
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
	void specialKeyPressed(int key, const PxTransform& camera) override;
};
