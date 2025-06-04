#pragma once

#include "Scene.h"
class StaticRigidBody;
class DynamicRigidBody;

class Level : public Scene
{
	std::vector<DynamicRigidBody*> drbs; // vector of dynamic rigid bodies
	size_t cDrb = 0; // current dynamic rigid body
	double stepAngle = 0.05;

public:
	Level(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Scene(cam, gphys, gscn) {}
	~Level() override;

	void setup() override {}
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
	void specialKeyPressed(int key, const PxTransform& camera) override;
};
