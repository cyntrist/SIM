#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem(Scene* scn) : System(scn)
{
}

ForceSystem::~ForceSystem()
{
}

void ForceSystem::affectParticles(const unordered_map<string, ObjInfo>& gameObjects, double t)
{
	for (auto p : gameObjects)
	{
		for (auto g : forceGenerators)
		{
			if (g->onRadius(p.second.gameObject))
			{
				p.second.gameObject->addForce(g->generateForce(*p.second.gameObject));
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
