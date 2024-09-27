#pragma once
//#include <foundation/Px.h>
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc = Vector3(10,0,0), double dampener = 0.98);
	~Particle();
	void integrate(double t);
	void setColor(double r, double g, double b, double a) 
	{ 
		renderItem->color = Vector4(r, g, b, a);
	}
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acc;
	double dampener;
};

