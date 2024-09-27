#pragma once
//#include <foundation/Px.h>
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, double dampener = 0.98, double acc = 1);
	~Particle();
	void integrate(double t);

private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double dampener;
	double acc;
};

