#include "Particle.h"

constexpr int LOW_TRESH = 10;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, 
	 float size, double dampener, double weight, double lifetime, double acttime)
	:  vel(vel), pose(pos), acc(acc), dampener(dampener), size(size),
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
	delete renderItem;
	renderItem = nullptr;
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

	if (pose.p.y <= -10)
		kill();

	acttime += t;
	integrate(t);
	return true;
}

bool Particle::integrate(double t)
{
	//pose.p += vel * t;
	//vel += acc * t;
	//vel *= pow(dampener, t);

	vel *= pow(dampener, t);
	vel += acc * t;
	pose.p += vel * t;

	return true;
}
