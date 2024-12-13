#pragma once
#include "Scene.h"

class RigidBodyScene : public Scene
{
public:
	RigidBodyScene(Camera* cam, physx::PxPhysics* gPhycs, physx::PxScene* gScn);
	void setup()override;
};

