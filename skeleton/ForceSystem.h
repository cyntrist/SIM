#pragma once
#include <vector>
#include "System.h"
#include "ForceGenerator.h"

using namespace std;

class ForceSystem : public System
{
private:
	vector<ForceGenerator*> forceGenerators;
public:
	ForceSystem(Scene* scn);
	~ForceSystem();

	void affectParticles(unordered_map<string, ObjInfo>const& gameObjects, double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
};

