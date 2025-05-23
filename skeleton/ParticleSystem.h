#pragma once

#include <random>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Scene.h"

class ParticleSystem : public System
{
	std::vector<ParticleGenerator*> particleGenerators;

public:
	ParticleSystem(Scene* sc) : System(sc) { }

	~ParticleSystem() override
	{
		for (auto gen : particleGenerators)
			delete gen;
	};

	bool update(double t) override
	{
		for (auto gen : particleGenerators)
			gen->update(t);
		return true;
	}

	void addParticleGenerator(ParticleGenerator* gen)
	{
		particleGenerators.push_back(gen);
		gen->setScene(scene);
	}

	void destroyParticleGenerator(int i)
	{
		particleGenerators.erase(std::find(particleGenerators.begin(), particleGenerators.end(),
		                                   particleGenerators[i]));
	}
};
