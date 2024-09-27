#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, double dampener, double acc) 
	: pose(pos), vel(vel), dampener(dampener), acc(acc)
{
	renderItem = new RenderItem(CreateShape(
		physx::PxSphereGeometry(10)), 
		&pose, 
		Vector4(1, 1, 1, 1)
	);
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	renderItem = nullptr;
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
	//vel += acc * t;
	vel *= pow(dampener, t);
}
