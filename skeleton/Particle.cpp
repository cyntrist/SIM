#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double dampener, int size)
	:  vel(vel), pose(pos), acc(acc), dampener(dampener), size(size)
{
	renderItem = new RenderItem(CreateShape(
		physx::PxSphereGeometry(size)),
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

bool Particle::integrate(double t)
{
	pose.p += vel * t;
	vel += acc * t;
	vel *= pow(dampener, t);

	//vel *= pow(dampener, t);
	//vel += acc * t;
	//pose.p += vel * t;

	return true;
}
