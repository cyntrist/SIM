#pragma once
#include "System.h"
#include "RigidBodyGenerator.h"

class RigidBodySystem : public System
{
protected:
	bool active = true;
	std::vector<RigidBodyGenerator*> rigidGenerators;
	PxPhysics* gphys;
	PxScene* gscn;
	Level* level;
	vector<Vector3> forces;

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
		if (!active) return false;
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

	void setActive(bool a = true) { active = a; }
	bool getActive() const { return active;  }
};
