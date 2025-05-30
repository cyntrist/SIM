#pragma once
#include "GameObject.h"
#include <PxPhysicsAPI.h>

#include "Scene.h"

class RigidBody : public GameObject
{
public:
	RigidBody(Scene* scn) : GameObject(scn) {}

	virtual PxRigidActor* getActor() { return nullptr; };
};

class StaticRigidBody : public RigidBody
{
	PxRigidStatic* actor = nullptr;

public:
	StaticRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene);
	~StaticRigidBody() override;
	Vector3 getPosition() override { return actor->getGlobalPose().p; }

	void setPosition(PxVec3 pos = {0,0,0}) override
	{
		RigidBody::setPosition(pos);
		actor->setGlobalPose(*pose);
	}
	void setShape(PxShape* shp, float siz = 1) override
	{
		GameObject::setShape(shp, siz);
		actor->attachShape(*shape);
	}
	void setVisible(bool vis = true) override
	{
		GameObject::setVisible(vis);
		scene->setActorVisible(actor, vis);
	}
};

class DynamicRigidBody : public RigidBody
{
	PxRigidDynamic* actor = nullptr;
	float density = 1.5;

public:
	DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene);
	~DynamicRigidBody() override;

	//setters
	void setPosition(PxVec3 pos = { 0,0,0 }) override
	{
		RigidBody::setPosition(pos);
		actor->setGlobalPose(*pose);
	}
	void setShape(PxShape* shp, float siz = 1) override
	{
		GameObject::setShape(shp, siz);
		actor->attachShape(*shape);
	}
	void setVisible(bool vis = true) override
	{
		GameObject::setVisible(vis);
		scene->setActorVisible(actor, vis);
	}
	void setDensity(float d) { density = d; }
	void setRotation(PxQuat rot) override
	{
		*pose = actor->getGlobalPose();
		pose->q = rot;
		actor->setGlobalPose(*pose);
	}
	void setMass(float mas) override
	{
		actor->setMass(mas);
		mass = mas;
	}

	// getters
	PxRigidActor* getActor() override { return actor; }
	Vector3 getPosition() override { return actor->getGlobalPose().p; }
	Vector3 getVelocity() override { return actor->getLinearVelocity(); }
	PxQuat getRotation() override { return actor->getGlobalPose().q; }
	float getMass() const override { return actor->getMass(); }

	void addForce(float x, float y, float z) override { actor->addForce({ x,y,z }); }
};
