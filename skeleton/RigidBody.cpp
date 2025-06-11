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
                                   double m, double s, double d, PxVec3 angVel, PxVec3 tensor)
	: RigidBody(scn), gScene(gScene), lifetime(life), maxLifetime(maxLife), sh(sh), generator(rbg),
	  gMaterial(mat)
{
	mass = m;
	size = s;
	auto volumen = 1;
	switch (sh)
	{
	case BOX:
		shape = CreateShape(PxBoxGeometry(vol), mat);
		volumen = vol.x * vol.y * vol.z;
		break;
	case SPHERE:
		shape = CreateShape(PxSphereGeometry(vol.x), mat);
		volumen = pow(vol.x, 3) * 4 / 3 * PxPi;
		size = vol.x; // tamano de una esfera es el radio
		break;
	case CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(vol.x, vol.y), mat);
		volumen = vol.x * vol.y * vol.z;
		break;
	}
	pose = new PxTransform(pos);
	actor = gPhysics->createRigidDynamic(*pose);
	//actor->userData = reinterpret_cast<void*>(this);
	actor->userData = static_cast<void*>(this);
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, Vector4(0.5, 0.5, 0.5, 1));
	setGroup(group);


	if (d <= 0)
		density = m / volumen;
	else
		density = d;

	if (tensor != PxVec3(1))
	{
		actor->setMass(mass);
		actor->setMassSpaceInertiaTensor(vol);
	}
	else
		PxRigidBodyExt::updateMassAndInertia(*actor, density);

	setKinematic(kin);
	if (!kin)
	{
		actor->setLinearVelocity(vel);
		actor->setAngularVelocity(angVel);
	}
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

	pose->p = actor->getGlobalPose().p;

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

Receiver::Receiver(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, bool kin, PxVec3 vol, PxVec3 pos, float mass,
                   float size, float density)
	: DynamicRigidBody(scn, gPhysics, gScene, nullptr, kin, CAPSULE,
	                   vol, pos, {0, 0, 0}, -1, -1, nullptr, eGRIDDLES,
	                   mass, size, density)
{
	setColor(offColor);
}

bool Receiver::collisionCallback()
{
	setColor(onColor);
	hasWon = true;
	return true;
}

bool Receiver::update(double t)
{
	pose->p = actor->getGlobalPose().p;
	if (!forces.empty())
		applyForce();
	//Log("POSE:");
	//Log(to_string(pose->p.y));
	//Log("ACTOR:");
	//Log(to_string(actor->getGlobalPose().p.y));
	return hasWon;
}

void Receiver::applyForce()
{
	DynamicRigidBody::applyForce();
}

void Receiver::addForce(const Vector3& fc)
{
	DynamicRigidBody::addForce(fc);
}

void Receiver::addForce(float x, float y, float z)
{
	//actor->addForce({ x,y,z }, PxForceMode::eFORCE);
	PxRigidBodyExt::addForceAtPos(*actor, {x,y,z}, 
		actor->getGlobalPose().p + PxVec3(0,3,0),
		PxForceMode::eFORCE
	);
}
