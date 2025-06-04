#pragma once

#include "Scene.h"
class StaticRigidBody;
class DynamicRigidBody;

class TestScene : public Scene
{
	StaticRigidBody* srb = nullptr;
	DynamicRigidBody* drb = nullptr;
	double stepAngle = 0.05;

public:
	TestScene(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Scene(cam, gphys, gscn) {}
	~TestScene();

	void setup() override {}
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
};
