#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Particle* model, Mode mode) : modo(mode), model(model)
{
	origin = model->getPose().p;
	max_life = model->getLifetime();
	ini_speed = model->getVel();
}

ParticleGenerator::ParticleGenerator(Vector3 origin, Vector3 speed, double max_life, Mode mode)
	: modo(mode), max_life(max_life), origin(origin), ini_speed(speed)
{
}

bool ParticleGenerator::update(double t)
{
	if (shouldGenerate())
		particles.push_back(addParticle());

	for (auto particle : particles)
		particle->update(t);


	for (int i = 0; i < particles.size(); i++)
	{
		if (!particles[i]->isAlive())
		{
			delete particles[i];
			auto ref = std::find(particles.begin(), particles.end(), particles[i]);
			particles.erase(ref);
			i--;
		}
	}

	return true;
}

Particle* ParticleGenerator::addParticle()
{
	Particle* part;
	switch (modo)
	{
	case Mode::FUENTE:
		{
			std::normal_distribution<> probability(5.0, 3.0);

			Vector3 newVel;
			newVel.x = probability(rd);
			newVel.y = probability(rd);
			newVel.z = probability(rd);

			part = new Particle(
				origin,
				newVel + ini_speed,
				Vector3(0, -10, 0)
			);
			part->setColor(0.1, 1.0, 0.2, 1);

			break;
		}
	case Mode::FUEGOS:
		{
			std::normal_distribution<> probability(1.0, 5.0);

			Vector3 newVel;
			newVel.x = probability(rd);
			newVel.y = probability(rd);
			newVel.z = probability(rd);

			part = new Particle(
				origin,
				newVel + ini_speed,
				Vector3(0, -10, 0)
			);
			part->setColor(1.0, 0.2, 0.1, 1);

			break;
		}
	case Mode::HUMO:
		{
			std::normal_distribution<> probability(10.0, 2.0);

			Vector3 newVel;
			newVel.x = probability(rd);
			newVel.y = probability(rd);
			newVel.z = probability(rd);

			part = new Particle(
				origin,
				newVel + ini_speed,
				Vector3(0, -10, 0)
			);
			part->setColor(0.1, 0.2, 1.0, 1);

			break;
		}
	}
	num++;

	return part;
}

bool ParticleGenerator::shouldGenerate()
{
	std::uniform_int_distribution<> distr(0, 4); // define the range
	return num < max_num && distr(mt) == 1;
}
