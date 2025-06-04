#pragma once
#include "GameObject.h"
#include <PxPhysicsAPI.h>
#include <cmath>
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
	void setRotation(PxQuat rot) override
	{
		*pose = actor->getGlobalPose();
		pose->q = rot;
		actor->setGlobalPose(*pose);
	}
};

class DynamicRigidBody : public RigidBody
{
	PxRigidDynamic* actor = nullptr;
	float density = 1;
	double angle = 0;

public:
	DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, 
		PxVec3 vol = { 10, 10, 10}, PxVec3 pos = { 0, 0, 0});
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
	//void setRotation(PxQuat rot) override
	//{
	//	*pose = actor->getGlobalPose();
	//	pose->q = rot;
	//	actor->setGlobalPose(*pose);
	//}
	void setRotation(double rot, PxVec3 axis = { 0, 0, 1})
	{
		angle += rot;

		PxTransform c = actor->getGlobalPose();
		PxQuat q(angle, axis); 
		PxTransform newPose(c.p, q);

		actor->setGlobalPose(newPose);
		actor->setKinematicTarget(newPose);

		if (!pose->isValid()) 
			std::cerr << "Transform inválido\n";
	}
	void setMass(float mas) override
	{
		actor->setMass(mas);
		mass = mas;
	}
	void setKinematic(bool k)
	{
		actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, k);
	}

	// getters
	PxRigidActor* getActor() override { return actor; }
	Vector3 getPosition() override { return actor->getGlobalPose().p; }
	PxQuat getRotation() override { return actor->getGlobalPose().q; }
	Vector3 getVel() override { return actor->getLinearVelocity(); }
	float getMass() const override { return actor->getMass(); }

	void addForce(float x, float y, float z) override { actor->addForce({ x,y,z }); }
};
