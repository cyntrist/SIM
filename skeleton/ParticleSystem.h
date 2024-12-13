#pragma once

#include <random>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Scene.h"

class ParticleSystem : public GameObject
{
	std::vector<ParticleGenerator*> generators;
	Scene* scene;

public:
	ParticleSystem(Scene* scene) : scene(scene)
	{
	}

	~ParticleSystem() = default;

	bool update(double t) override
	{
		for (auto gen : generators)
			gen->update(t);
		return true;
	};

	void addGenerator(ParticleGenerator* gen)
	{
		generators.push_back(gen);
		gen->setScene(scene);
	};

	void destroyGenerator(int i)
	{
		generators.erase(std::find(generators.begin(), generators.end(), generators[i]));
	};
};
