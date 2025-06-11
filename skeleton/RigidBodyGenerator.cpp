#include "RigidBodyGenerator.h"

RigidBodyGenerator::RigidBodyGenerator(Vector3 org, int stNpart, PxPhysics* gphys, PxScene* gscn,
                                       RigidBodySystem* partsys, PxVec3 vel,
                                       double min, double max, double freq,
                                       PxVec4 color,
                                       float mass, float size, float density,
                                       PxVec3 angVel, PxVec3 tensor, bool nonlinear, bool wave)
	: gphys(gphys), gscn(gscn), origen(org), system(partsys), maxGameObjects(stNpart), timer(freq),
	  velocity(vel), minLife(min), maxLife(max), color(color), mass(mass), size(size), density(density),
	  dummyAngVel(angVel), tensor(tensor), nonlinear(nonlinear), wave(wave)
{
}

void RigidBodyGenerator::update(double t)
{
	if (mayGenerate())
		generateBody(t);
}

void RigidBodyGenerator::generateBody(double t)
{
	PxVec3 volumen = {size, size, size}; // esferas de 2 de diametro
	PxMaterial* mat = nullptr;
	// color
	if (hsvColor >= 360)
		sentido = -1;
	if (hsvColor <= 0)
		sentido = 1;
	hsvColor = hsvColor + angStep * sentido;
	color = hsvToRgb(hsvColor);

	auto vel = velocity;
	if (nonlinear)
	{
		auto sigma = 0.5;
		normal_distribution<> xDist(0, sigma);
		vel.x += xDist(generator);
	}
	else if (wave)
	{
		angle += 0.5;
		vel.x += PxCos(angle) * 2;
	}

	auto drb1 = new DynamicRigidBody(
		scene, gphys, gscn, mat,
		false, SPHERE, volumen,
		origen, vel,
		minLife, maxLife,
		this, eDROPS,
		mass, size, density,
		{0,0,0},
		tensor
	);
	drb1->setColor(color);
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
		false, SPHERE, {size, size, size},
		origen, {0, 0, 0},
		-1, -1,
		this, eDROPS, 1, 1, -1
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
