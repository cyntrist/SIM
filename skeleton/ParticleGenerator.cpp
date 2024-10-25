#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
}

bool ParticleGenerator::update(double t)
{
	if (shouldGenerate())
		particles.push_back(addParticle());

	for (const auto particle : particles)
		particle->update(t);

	for (const auto particle : particles)
	{
		if (!particle->isAlive())
		{
			delete particle;
			particles.erase(std::find(particles.begin(), particles.end(), particle));
		}
	}
}

Particle* ParticleGenerator::addParticle()
{
	num++;
	return new Particle(origin, ini_speed);;
}

bool ParticleGenerator::shouldGenerate()
{
	return num < max_num;
}

