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

DynamicRigidBody::DynamicRigidBody(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, PxMaterial* mat,
                                   bool kin, Shape sh, PxVec3 vol, PxVec3 pos, PxVec3 vel,
                                   double life, double maxLife, RigidBodyGenerator* rbg, PxU32 group,
                                   float m, float s, float d)
	: RigidBody(scn), gScene(gScene), lifetime(life), maxLifetime(maxLife), sh(sh), generator(rbg),
	  gMaterial(mat)
{
	auto volumen = 1;
	switch (sh)
	{
	case BOX:
		shape = CreateShape(PxBoxGeometry(vol), mat);
		volumen = vol.x * vol.y * vol.z;
		break;
	case SPHERE:
		shape = CreateShape(PxSphereGeometry(vol.x), mat);
		volumen = vol.x * vol.x * vol.x * 4 / 3 * PxPi;
		break;
	case CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(vol.x, vol.y), mat);
		volumen = vol.x * vol.y * vol.z;
		break;
	}
	pose = new PxTransform(pos);
	actor = gPhysics->createRigidDynamic(*pose);
	actor->attachShape(*shape);
	setGroup(group);

	mass = m;
	size = s;
	density = d;
	//density = m/volumen;
	
	//actor->setMass(mass);
	actor->setLinearVelocity(vel);
	//actor->setMassSpaceInertiaTensor(vol);
	//actor->setMassSpaceInertiaTensor(vol);
	//actor->setAngularVelocity({0, 0, 0});
	//PxRigidBodyExt::updateMassAndInertia(*actor, density);
	PxRigidBodyExt::updateMassAndInertia(*actor, density);


	setKinematic(kin);
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
	for (auto f : forces)
		addForce(f.x, f.y, f.z); // physx ya calcula f=m/a por si solo
	forces.clear();
}

void DynamicRigidBody::addForce(float x, float y, float z)
{
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

	if (!forces.empty())
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
