#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "GameObject.h"

class Particle : public GameObject
{
public:
	Particle(const Particle& other);
	Particle(string nam, Scene* scn, Vector3 Pos);
	Particle(string nam, Scene* scn, Vector3 pos, Vector3 vel, Vector3 acc = Vector3(0, 0, 0),
	         float size = 1, double dampener = 0.98, double weight = 1, double lifetime = 10,
	         double acttime = 0);
	~Particle() override;

	bool update(double t) override;
	bool integrate(double t);

	// setters
	void setColor(double r, double g, double b, double a) const
	{
		renderItem->color = Vector4(r, g, b, a);
	}

	void setColor(Vector4 col) override
	{
		renderItem->color = col;
		color = col;
	}

	void setPose(PxTransform* p)						{ pose = p; }
	void setAcc(const Vector3& a = {0, 0, 0}) { acc = a; }
	void setDamp(double d = 0.98)						{ dampener = d; }
	void setMaxLifetime(double a)						{ maxLifetime = a; }
	void setLifetime(double a)							{ lifetime = a; }

	// getters
	Vector4 getColor() const							{ return renderItem->color; }
	PxTransform* getPose() const						{ return pose; }
	Vector3 getAcc() const								{ return acc; }
	double getDamp() const								{ return dampener; }
	double getLifetime() const							{ return lifetime; }
	double getMaxLifetime() const						{ return maxLifetime; }
	Vector3 getGrav() const								{ return grav; }
	ParticleGenerator* getGenerator() const				{ return generator; }

	void toggleGrav()
	{
		gravitable = !gravitable;
	}

	// fuerzas
	void addForce(float x, float y, float z) override	{ forces.push_back({x, y, z}); }
	void addForce(const Vector3& fc) override			{ forces.push_back(fc); }
	void applyForce();
	void setGravitable(bool g)							{ gravitable = g; }
	void setImmovible(bool i)							{ immovible = i; }
	void setFloor(float h)								{ floor = h; }
	void setGenerator(ParticleGenerator* gen)			{ generator = gen;  }

private:
	Vector3 acc;
	double dampener;
	double lifetime;
	double maxLifetime = -1;
	Vector3 grav = Vector3(0, -9.8, 0);
	bool gravitable = false;
	bool immovible = false;
	vector<Vector3> forces;
	float floor = 0;
	ParticleGenerator* generator = nullptr;
};
