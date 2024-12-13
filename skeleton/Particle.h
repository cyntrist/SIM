#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "GameObject.h"

class Particle : public GameObject
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc = Vector3(0, 0, 0),
	         float size = 1, double dampener = 0.98, double weight = 1, double lifetime = 10,
	         double acttime = 0);

	virtual ~Particle();

	bool update(double t) override;
	bool integrate(double t);

	// setters
	void setColor(double r, double g, double b, double a) const
	{
		renderItem->color = Vector4(r, g, b, a);
	}

	void setVel(const Vector3& v = {0, 0, 0}) { vel = v; }
	void setPose(const physx::PxTransform& p) { pose = p; }
	void setAcc(const Vector3& a = {0, 0, 0}) { acc = a; }
	void setDamp(double d = 0.98) { dampener = d; }

	// getters
	Vector4 getColor() const { return renderItem->color; }
	Vector3 getVel() const { return vel; }
	physx::PxTransform getPose() const { return pose; }
	Vector3 getAcc() const { return acc; }
	double getDamp() const { return dampener; }
	float getSize() const { return size; }
	double getWeight() const { return weight; }
	double getLifetime() const { return lifetime; }
	double getActtime() const { return acttime; }
	Vector3 getGrav() const { return grav; }

	// fuerzas:
	void addForce(float x, float y, float z) override { forces.push_back({ x,y,z }); }
	void addForce(Vector3 fc) override { forces.push_back(fc); }
	void applyForce();

private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acc;
	double dampener;
	float size;
	double weight;
	double lifetime;
	double acttime = 10;
	bool alive = true;
	Vector3 grav = Vector3(0, -9.8, 0);
};
