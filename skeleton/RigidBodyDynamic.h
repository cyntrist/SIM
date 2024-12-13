﻿#pragma once
#include "RigidBodyActor.h"

class RBDynamic : public RBActor
{
public:
	RBDynamic(string nam, Scene* scn, PxPhysics* gPhysics);
	~RBDynamic() override;

	bool update(double t) override { return RBActor::update(t); }

	//setters
	void setPosition(PxVec3 pos) override
	{
		GameObject::setPosition(pos);
		actor->setGlobalPose(*pose);
	};
	void setShape(PxShape* shp, float siz) override;
	void setDensity(float d) { density = d; };
	void setVisible(bool vis) override;
	// getters
	PxRigidActor* getActor() override { return actor; };
	Vector3 getPosition() override { return actor->getGlobalPose().p; };

	void addForce(float x, float y, float z) override { actor->addForce({x, y, z}); }
	void addForce(Vector3 fc) override { actor->addForce(fc); }

private:
	PxRigidDynamic* actor = nullptr;
	float density = 1.5;
};
