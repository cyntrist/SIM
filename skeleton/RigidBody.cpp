#include "RigidBody.h"

StaticRigidBody::StaticRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene)
	: RigidBody(scn)
{
	PxVec3 pos(0, 0, 0);
	PxVec3 volume = {size, size, size};

	pose = new PxTransform(pos);
	actor = gPhysics->createRigidStatic(*pose);
	shape = CreateShape(PxBoxGeometry(volume));
	actor->attachShape(*shape);

	renderItem = new RenderItem(shape, actor, {0.7, 0.7, 0.7, 1});
}

StaticRigidBody::~StaticRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}

DynamicRigidBody::DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene,
                                   bool kin, Shape sh, PxVec3 vol, PxVec3 pos, PxVec3 vel)
	: RigidBody(scn)
{
	density = 1.f;
	pose = new PxTransform(pos);
	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity(vel);
	actor->setAngularVelocity({0, 0, 0});
	actor->setMassSpaceInertiaTensor(vol);
	setKinematic(kin);
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	size = 1;

	switch (sh)
	{
	case BOX:
		shape = CreateShape(PxBoxGeometry(vol));
		break;
	case SPHERE:
		shape = CreateShape(PxSphereGeometry(vol.x));
		break;
	case CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(vol.x, vol.y));
		break;
	}

	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, Vector4(0.5, 0.5, 0.5, 1));
}

DynamicRigidBody::~DynamicRigidBody()
{
	DeregisterRenderItem(renderItem);
	delete pose;
	delete renderItem;
}
