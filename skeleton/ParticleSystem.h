#pragma once

#include <list>
#include "Particle.h"

class ParticleSystem
{
	std::list<Particle> particles;
	// origen (todo est oes el generator)
	// velocidad media
	//duracion
	//particula modelo
	// probabilidad


public:
	ParticleSystem();
	~ParticleSystem();

	bool update(double t);
	void addParticle();
	void destroyParticle();

};

