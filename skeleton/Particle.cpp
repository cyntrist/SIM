#include "Particle.h"

#include <iostream>

constexpr int LOW_TRESH = 10;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc,
                   float size, double dampener, double weight, double lifetime, double acttime)
	: vel(vel), pose(pos), acc(acc), dampener(dampener), size(size),
	  weight(weight), lifetime(lifetime), acttime(acttime)
{
	renderItem = new RenderItem(CreateShape(
		                            physx::PxSphereGeometry(this->size)),
	                            &pose,
	                            Vector4(1, 1, 1, 1)
	);
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

bool Particle::update(double t)
{
	if (!alive)
		return false;

	if (acttime > lifetime || pose.p.y <= -LOW_TRESH)
	{
		kill();
		return false;
	}

	acttime += t;
	integrate(t);
	return true;
}

bool Particle::integrate(double t)
{
	vel *= pow(dampener, t);
	vel += acc * t;
	pose.p += vel * t;

	return true;
}
