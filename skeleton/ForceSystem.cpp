#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem(Scene* scn) : System(scn) { }

ForceSystem::~ForceSystem()
{
	for (auto gen : forceGenerators)
		delete gen;
	forceGenerators.clear();
}

void ForceSystem::affectParticles(const vector<GameObject*>& gameObjects, double t)
{
	for (auto g : gameObjects)
	{
		for (auto f : forceGenerators)
		{
			if (f->onRadius(g))
			{
				g->addForce(f->generateForce(*g));
			}
		}
	}

	for (auto g : forceGenerators)
	{
		g->update(t);
	}
}


void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}
