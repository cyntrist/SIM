#pragma once
#include <vector>
#include "ForceGenerator.h"

class Scene;
using namespace std;

class ForceSystem
{
	vector<ForceGenerator*> generators;
	Scene* scene;

public:
	ForceSystem();
	~ForceSystem() = default;

	bool update(double t)
	{
		for (auto gen : generators)
			gen->update(t);
		return true;
	}

	void addGenerator(ForceGenerator* gen)
	{
		generators.push_back(gen);
		gen->setScene(scene);
	}

	void destroyGenerator(int i)
	{
		generators.erase(std::find(generators.begin(), generators.end(), generators[i]));
	}
};
