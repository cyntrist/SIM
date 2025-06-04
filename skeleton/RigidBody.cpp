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

	renderItem = new RenderItem(shape, actor, { 0.7,0.7,0.7,1 });
}

StaticRigidBody::~StaticRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}

DynamicRigidBody::DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, 
	bool kin, PxVec3 vol, PxVec3 pos)
	: RigidBody(scn)
{
	density = 1.f;
	pose = new PxTransform(pos);
	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	actor->setMassSpaceInertiaTensor(vol);
	setKinematic(kin);
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	size = 1;
	shape = CreateShape(PxBoxGeometry(vol));
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, Vector4(0.5, 0.5, 0.5, 1));
}

DynamicRigidBody::~DynamicRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}
