#include "Particle.h"

#include <iostream>

constexpr int LOW_TRESH = 10;

Particle::Particle(const Particle& other) : GameObject(other.name, other.scene)
{
	pose = new PxTransform(other.pose->p);
	vel = other.vel;
	acc = other.acc;
	dampener = other.dampener;
	size = other.size;
	maxLifetime = other.maxLifetime;
	shape = other.shape;
	color = {0.5, 1, 1, 1.0};
	renderItem = new RenderItem(shape, pose, color);
}

Particle::Particle(string nam, Scene* scn, Vector3 Pos) : GameObject(nam, scn)
{
	pose = new PxTransform(Pos);
	vel = {0, 0, 0};
	acc = {0, 0, 0};
	dampener = 0.8;
	size = 5;
	maxLifetime = 10;
	shape = CreateShape(PxSphereGeometry(size));
	color = {0.5, 1, 1, 1.0};
	renderItem = new RenderItem(shape, pose, color);
}

Particle::Particle(string nam, Scene* scn, Vector3 pos, Vector3 vel, Vector3 acc,
                   float size, double dampener, double weight, double lifetime, double acttime)
	: GameObject(nam, scn), acc(acc), dampener(dampener), size(size),
	  lifetime(lifetime), maxLifetime(acttime)
{
	//mass = weight;
	//this->vel = vel;
	//this->pose = pose;
	//renderItem = new RenderItem(CreateShape(
	//	                            PxSphereGeometry(this->size)),
	//                            &pose,
	//                            Vector4(1, 1, 1, 1)
	//);
	//RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	//DeregisterRenderItem(renderItem);
}

bool Particle::update(double t)
{
	if (!alive)
		return false;

	if (lifetime > maxLifetime || pose->p.y <= -LOW_TRESH)
	{
		kill();
		return false;
	}

	lifetime += t;
	integrate(t);
	return true;
}

bool Particle::integrate(double t)
{
	vel += acc * t;
	pose->p += vel * t;

	// se hace el damping siempre lo ultimo
	vel *= pow(dampener, t);
	return true;
}

void Particle::applyForce()
{
	// calculamos la fuerza acumulada
	Vector3 totalForc = {0, 0, 0};
	for (auto f : forces)
		totalForc += f;
	forces.clear();

	// F=m*a
	acc = totalForc / mass;

	// Aplica la gravedad si es un objeto con gravedad
	if (gravitable)
		acc += grav;
}
