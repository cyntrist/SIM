#include "RigidBodyGenerator.h"

RigidBodyGenerator::RigidBodyGenerator(Vector3 org, int stNpart, PxPhysics* gphys, PxScene* gscn,
                                       RigidBodySystem* partsys, PxVec3 vel,	
                                       double min, double max, double freq)
	: gphys(gphys), gscn(gscn), origen(org), system(partsys), maxGameObjects(stNpart), timer(freq),
	  velocity(vel), minLife(min), maxLife(max)
{
}

void RigidBodyGenerator::update(double t)
{
	if (mayGenerate())
		generateBody(t);
}

void RigidBodyGenerator::generateBody(double t)
{
	PxVec3 volumen = {1,1,1}; // esferas de 2 de diametro

	auto c = color;

	//double mass = 1;
	//double density = 1;
	//double size = 1;
	//if (sw)
	//{
	//	size = 1000;
	//	density = 1000;
	//	mass = 1000;
	//	c = Vector4(1, 0, 0, 1);
	//}
	//sw = !sw;

	PxMaterial* mat = nullptr;
	auto drb1 = new DynamicRigidBody(
		scene, gphys, gscn, mat,
		false, SPHERE, volumen,
		origen, velocity,
		0, 30,
		this, eDROPS,
		1,volumen.x,-1, 
		{ 10, 0, 0 }
	);

	drb1->setColor(c);
	drb1->setVisible(true);

	scene->addGameObject(drb1);
	addNumBodies(1);
}

bool RigidBodyGenerator::mayGenerate()
{
	if (nGameObjects >= maxGameObjects)
		return false;
	counter += 1;
	if (counter >= timer)
	{
		counter = 0;
		return true;
	}
	return false;
}

void RigidBodyGenerator::setDummy()
{
	float size = 2.5;
	dummy = new DynamicRigidBody(
		scene, gphys, gscn, nullptr,
		false, SPHERE, {size,size,size},
		origen, { 0,0,0 },
		-1, -1,
		this, eDROPS, 1,1,-1
	);
	dummy->setColor(color);
	//dummy->setColor(PxVec4(0.98,0.64,0.01,1.0));
	dummy->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	dummy->setDamping(0.0);
	dummy->setAngularVelocity(dummyAngVel);
	scene->addGameObject(dummy);
}

void RigidBodyGenerator::toggleDummyMovement(bool active)
{
	if (active)
		dummy->setAngularVelocity(dummyAngVel);
	else
		dummy->setAngularVelocity(PxVec3(0.0f));
}
