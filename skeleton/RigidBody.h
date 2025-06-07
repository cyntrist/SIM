#pragma once
#include "GameObject.h"
#include <PxPhysicsAPI.h>
#include "Scene.h"

class RigidBodyGenerator;

enum Shape { BOX, SPHERE, CAPSULE };

class RigidBody : public GameObject
{
public:
	RigidBody(Scene* scn) : GameObject(scn) {}

	virtual PxRigidActor* getActor() { return nullptr; }
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
	PxScene* gScene = nullptr;
	PxMaterial* gMaterial = nullptr;
	float density = 1;
	double angle = 0;
	double lifetime = -1;
	double maxLifetime = -1;
	RigidBodyGenerator* generator = nullptr;
	vector<Vector3> forces;
	Shape sh;

public:
	DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, bool kin = false,
		Shape sh = SPHERE, PxVec3 vol = { 1, 1, 1}, PxVec3 pos = { 0, 0, 0},
		PxVec3 vel = { 0, 0, 0 }, double lifetime = -1, double maxLifetime = -1,
		PxMaterial* mat = nullptr);
	~DynamicRigidBody() override;

	//setters
	void setLinearVelocity(PxVec3 vel = { 0, 0, 0 })
	{
		RigidBody::setVel(vel);
		actor->setLinearVelocity(vel);
	}
	void setAngularVelocity(PxVec3 vel = { 0, 0, 0 })
	{
		actor->setAngularVelocity(vel);
	}
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
	void setRotation(double rot, PxVec3 axis = { 0, 0, 1})
	{
		angle += rot;

		PxTransform c = actor->getGlobalPose();
		PxQuat q(angle, axis); 
		PxTransform newPose(c.p, q);

		actor->setGlobalPose(newPose);
		actor->setKinematicTarget(newPose);

		if (!pose->isValid())
			Log("Transform erroneo");
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
	void setGroup();

	// getters
	PxRigidActor* getActor() override { return actor; }
	Vector3 getPosition() override { return actor->getGlobalPose().p; }
	PxQuat getRotation() override { return actor->getGlobalPose().q; }
	Vector3 getVel() override { return actor->getLinearVelocity(); }
	float getMass() const override { return actor->getMass(); }
	bool update(double t) override;
	void addForce(float x, float y, float z) override;
};
