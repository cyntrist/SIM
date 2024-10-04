#pragma once
//#include <foundation/Px.h>
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc = Vector3(0,0,0), double dampener = 0.98, int size = 10);
	~Particle();
	bool integrate(double t);
	void setColor(double r, double g, double b, double a) const
	{ 
		renderItem->color = Vector4(r, g, b, a);
	}
	void setVel(const Vector3& v = { 0, 0, 0 }) { vel = v; }
	void setPose(const physx::PxTransform& p) { pose = p; }
	void setAcc(const Vector3& a = { 0, 0, 0 }) { acc = a; }
	void setDamp(double d = 0.98) { dampener = d; }
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acc;
	double dampener;
	int size;
};

