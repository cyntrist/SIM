#include "Particle.h"

#include <iostream>

#include "ParticleGenerator.h"
#include "Scene.h"

constexpr int LOW_TRESH = 200;

Particle::Particle(const Particle& other) : GameObject(other.scene)
{
	pose = new PxTransform(other.pose->p);
	vel = other.vel;
	acc = other.acc;
	dampener = other.dampener;
	size = other.size;
	lifetime = 0;
	maxLifetime = other.maxLifetime;
	shape = other.shape;
	color = {0.5, 1, 1, 1.0};
	renderItem = new RenderItem(shape, pose, color);
}

Particle::Particle(Scene* scn, Vector3 Pos, double siz) : GameObject(scn)
{
	pose = new PxTransform(Pos);
	vel = {0, 0, 0};
	acc = {0, 0, 0};
	dampener = 0.8;
	size = siz;
	shape = CreateShape(PxSphereGeometry(size));
	renderItem = new RenderItem(shape, pose, color);
	lifetime = 0;
	maxLifetime = -1;
	color = {0.5, 1, 1, 1.0};
}

Particle::Particle(Scene* scn, Vector3 pos, Vector3 vel, Vector3 acc,
                   float size, double dampener, double mass, double lifetime, double acttime)
	: GameObject(scn, size, mass), acc(acc), dampener(dampener),
	  lifetime(lifetime), maxLifetime(acttime)
{

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

bool Particle::update(double t)
{
	if (!alive)
		return false;

	if ((maxLifetime != -1 && lifetime > maxLifetime) 
		|| pose->p.y <= -scene->getLowerThreshold() 
		|| pose->p.y >= scene->getUpperThreshold())
	{
		kill();
		if (generator != nullptr)
		{
			//if (color == Vector4(0,1,0,1))
				//Log(to_string(generator->getNumParticles()));
			generator->addNumParticles(-1);
		}
		return false;
	}

	if (immovible) return true;

	applyForce();
	integrate(t);
	lifetime += t;
	return true;
}

bool Particle::integrate(double t)
{
	if (eulerSemiImplicito)
	{
		vel += acc * t;
		pose->p += vel * t;

		// se hace el damping siempre lo ultimo
		vel *= pow(dampener, t);
	}
	else
	{
		pose->p += vel * t;
		vel += acc * t;
		vel *= pow(dampener, t);
	}

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
