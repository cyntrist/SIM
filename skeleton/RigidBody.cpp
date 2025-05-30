#include "RigidBody.h"

StaticRigidBody::StaticRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene)
	: RigidBody(scn)
{
	PxVec3 pos(0, 0, 0);
	PxVec3 volume = { size,size,size };

	pose = new PxTransform(pos);
	actor = gPhysics->createRigidStatic(*pose);
	shape = CreateShape(PxBoxGeometry(volume));
	actor->attachShape(*shape);
	//gScene->addActor(*actor);

	renderItem = new RenderItem(shape, actor, { 0.7,0.7,0.7,1 });
}

StaticRigidBody::~StaticRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}



DynamicRigidBody::DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene)
	: RigidBody(scn)
{
	PxVec3 pos = { 0,0,0 };
	PxVec3 volume = { 10,10,10 };
	density = 1.5f;
	pose = new PxTransform(pos);
	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	actor->setMassSpaceInertiaTensor({ 10,10,10 });
	size = 1;
	//shape = CreateShape(PxBoxGeometry(volume));
	//gScene->addActor(*actor);

	shape = CreateShape(PxBoxGeometry(volume / 2));
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, { 0.87,0.87,0.87,1 });
}

DynamicRigidBody::~DynamicRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}
