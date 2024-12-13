﻿#pragma once
#include "RigidBodyActor.h"

class RBStatic : public RBActor
{
public:
	RBStatic(string nam, Scene* scn, PxPhysics* gPhysics);
	~RBStatic();

	bool update(double t) override { return RBActor::update(t); }

	PxRigidActor* getActor() override { return actor; }
	Vector3 getPosition() override { return actor->getGlobalPose().p; };
	void setShape(PxShape* shp, float siz) override;
	void setPosition(PxVec3 pos) override { GameObject::setPosition(pos); actor->setGlobalPose(*pose); };
	void setVisible(bool vis) override;
private:
	PxRigidStatic* actor;

};

