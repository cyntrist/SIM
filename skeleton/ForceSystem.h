#pragma once
#include <vector>
#include "System.h"
#include "ForceGenerator.h"

class ForceSystem : public System
{
	vector<ForceGenerator*> forceGenerators;

public:
	ForceSystem(Scene* scn) : System(scn) {}

	~ForceSystem() override
	{
		for (auto gen : forceGenerators)
			delete gen;
		forceGenerators.clear();
	}

	void affectParticles(const vector<GameObject*>& gameObjects, double t) override
	{
		for (auto g : gameObjects)
			for (auto f : forceGenerators)
				if (f->onRadius(g))
					g->addForce(f->generateForce(*g));

		for (auto g : forceGenerators)
			g->update(t);
	}

	void addForceGenerator(ForceGenerator* forcGen)
	{
		forceGenerators.push_back(forcGen);
	}
};
