#pragma once
#include "Scene.h"

class RigidBodyScene : public Scene
{
public:
	RigidBodyScene(Camera* cam = nullptr, PxPhysics* gPhycs = nullptr, PxScene* gScn = nullptr);
	void setup() override;
};
