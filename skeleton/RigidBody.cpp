#include "RigidBody.h"
#include "RigidBodyGenerator.h"

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
                                   bool kin, Shape sh, PxVec3 vol, PxVec3 pos, PxVec3 vel,
                                   double life, double maxLife, RigidBodyGenerator* rbg, PxU32 group,
                                   PxMaterial* mat, float m, float s, float d)
	: RigidBody(scn), gScene(gScene), lifetime(life), maxLifetime(maxLife), sh(sh), generator(rbg),
	  gMaterial(mat)
{
	switch (sh)
	{
	case BOX:
		shape = CreateShape(PxBoxGeometry(vol), mat);
		break;
	case SPHERE:
		shape = CreateShape(PxSphereGeometry(vol.x), mat);
		break;
	case CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(vol.x, vol.y), mat);
		break;
	}

	mass = m;
	size = s;
	density = d;

	pose = new PxTransform(pos);
	setGroup(group);

	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity(vel);
	actor->setAngularVelocity({0, 0, 0});
	actor->setMassSpaceInertiaTensor(vol);
	setKinematic(kin);
	PxRigidBodyExt::updateMassAndInertia(*actor, density);

	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, Vector4(0.5, 0.5, 0.5, 1));
}

DynamicRigidBody::~DynamicRigidBody()
{
	DeregisterRenderItem(renderItem);
	gScene->removeActor(*actor);
	actor->release();
	delete pose;
	delete renderItem;
}

void DynamicRigidBody::applyForce()
{
	Vector3 totalForc = {0, 0, 0};
	for (auto f : forces)
		totalForc += f;
	forces.clear();

	// F=m*a
	auto acc = totalForc / actor->getMass();

	addForce(acc);
}

void DynamicRigidBody::addForce(float x, float y, float z)
{
	RigidBody::addForce(x, y, z);
	actor->addForce({x, y, z});
}

void DynamicRigidBody::addForce(const Vector3& fc)
{
	forces.push_back(fc);
}

bool DynamicRigidBody::update(double t)
{
	if (!alive)
		return false;

	if ((maxLifetime != -1 && lifetime > maxLifetime)
		|| actor->getGlobalPose().p.y <= -scene->getLowerThreshold()
		|| actor->getGlobalPose().p.y >= scene->getUpperThreshold())
	{
		kill();
		if (generator != nullptr)
			generator->addNumBodies(-1);
		return false;
	}

	applyForce();
	lifetime += t;
	return true;
}

void DynamicRigidBody::setGroup(PxU32 group, bool autoexcludig)
{
	gScene->lockWrite();
	PxFilterData filterData;
	filterData.word0 = group;
	filterData.word1 = group;
	if (autoexcludig)
		filterData.word1 = ~group;
	shape->setSimulationFilterData(filterData);
	gScene->unlockWrite();
}
