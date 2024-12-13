﻿#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "GameObject.h"

using namespace std;
using namespace physx;

class RBActor : public GameObject
{
public:
	RBActor(string nam, Scene* scn, PxPhysics* gPhysics) : GameObject(nam, scn) {};
	virtual ~RBActor() = default;

	virtual bool update(double t) override { return true; }

	// visibilidad
	virtual void setVisible(bool vis) override { GameObject::setVisible(vis); };

	// getters:
	virtual PxRigidActor* getActor() { return nullptr; };

	virtual void setShape(PxShape* shp, float siz) override { GameObject::setShape(shp, siz); }
};

