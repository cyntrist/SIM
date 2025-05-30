#pragma once
#include "Scene.h"

class RigidBodyScene : public Scene
{

public:
	RigidBodyScene(PxPhysics* gphys, PxScene* gscn, Camera* cam = nullptr) : Scene(cam, gphys, gscn)
	{
	}
	void setup() override {}
	void onEnable() override;
	void onDisable() override;
};
