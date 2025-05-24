#pragma once
#include "Particle.h"
#include "Global.h"

class Scene;

class System
{
protected:
	double delta = 0;
	Scene* scene = nullptr;

public:
	System(Scene* scn) : scene(scn) { }
	virtual ~System() { }

	double getDelta() const { return delta; }
	void setScene(Scene* sc) { scene = sc; }
	virtual void affectParticles(const vector<GameObject*>& gameObjects, double t) { }

	virtual bool update(double t)
	{
		delta = t;
		return false;
	}
};
