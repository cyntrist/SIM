#pragma once
#include "Particle.h"
#include "Widget.h"
#include <unordered_map>
#include "Global.h"

using namespace std;
class Scene;

class System
{
protected:
	double delta = 0;
	Scene* scene = nullptr;

public:
	System(Scene* scn): scene(scn)
	{
	};

	~System()
	{
	};

	virtual bool update(double t)
	{
		delta = t;
		return false;
	};

	double getDelta() const { return delta; }

	virtual void affectParticles(const unordered_map<string, ObjInfo>& gameObjects, double t)
	{
	}
};
