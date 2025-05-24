#pragma once
#include <vector>
#include "System.h"
#include "ForceGenerator.h"

using namespace std;

class ForceSystem : public System
{
	vector<ForceGenerator*> forceGenerators;

public:
	ForceSystem(Scene* scn);
	~ForceSystem() override;

	void affectParticles(const vector<GameObject*>& gameObjects, double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
};
