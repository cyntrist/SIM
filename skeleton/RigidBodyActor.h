#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "GameObject.h"

using namespace std;
using namespace physx;

class RBActor : public GameObject
{
public:
	RBActor(string nam, Scene* scn, PxPhysics* gPhysics) : GameObject(nam, scn)
	{
	};
	~RBActor() override = default;

	bool update(double t) override { return true; }

	// visibilidad
	void setVisible(bool vis) override { GameObject::setVisible(vis); };

	// getters:
	virtual PxRigidActor* getActor() { return nullptr; };

	void setShape(PxShape* shp, float siz) override { GameObject::setShape(shp, siz); }
};
