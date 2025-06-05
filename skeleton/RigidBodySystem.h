#pragma once
#include "System.h"
#include "RigidBodyGenerator.h"

class RigidBodySystem : public System
{
protected:
	std::vector<RigidBodyGenerator*> rigidGenerators;
	PxPhysics* gphys;
	PxScene* gscn;
	Level* level;
		
public:
	RigidBodySystem(Scene* sc, PxPhysics* gphys, PxScene* gscn, Level* level)
	: System(sc), gphys(gphys), gscn(gscn), level(level) {}

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

	void addRBGenerator(RigidBodyGenerator* gen)
	{
		rigidGenerators.push_back(gen);
		gen->setScene(scene);
	}

	void destroyRBGenerator(int i)
	{
		rigidGenerators.erase(std::find(rigidGenerators.begin(), rigidGenerators.end(),
			rigidGenerators[i]));
	}
};
