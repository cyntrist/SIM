#pragma once

#include <random>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem : public SceneObject
{
	std::vector<ParticleGenerator*> generators;

public:
	ParticleSystem() = default;
	~ParticleSystem()  = default;

	bool update(double t) override
	{
		for (auto gen : generators)
			gen->update(t);
		return true;
	};
	void addGenerator(ParticleGenerator* gen)
	{
		generators.push_back(gen);
	};
	void destroyGenerator(int i)
	{
		generators.erase(std::find(generators.begin(), generators.end(), generators[i]));
	};
};

