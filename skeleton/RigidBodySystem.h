#pragma once
#include "System.h"

class RigidBodyGenerator;

class RigidBodySystem : System
{
protected:
	std::vector<RigidBodyGenerator*> rigidGenerators;

public:
	RigidBodySystem(Scene* sc) : System(sc) {}

	~RigidBodySystem() override
	{
		for (auto gen : rigidGenerators)
			delete gen;
	}

	bool update(double t) override
	{
		for (auto gen : rigidGenerators)
			gen->update(t);
		return true;
	}

	void addParticleGenerator(RigidBodyGenerator* gen)
	{
		rigidGenerators.push_back(gen);
		gen->setScene(scene);
	}

	void destroyParticleGenerator(int i)
	{
		rigidGenerators.erase(std::find(rigidGenerators.begin(), rigidGenerators.end(),
			rigidGenerators[i]));
	}
};
