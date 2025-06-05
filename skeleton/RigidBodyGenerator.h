#pragma once
#include <random>

#include "RigidBodySystem.h"


class RigidBodyGenerator
{
	RigidBodySystem* system;
	default_random_engine generator;

	Vector3 origen;
	Vector4 color = Vector4(1, 1, 1, 1);
	Scene* scene;
	int maxGameObjects = 100;
	int nGameObjects = 0;
	double minLife, maxLife;
	float mass = 1, size = 5;
	double dampener = 0.98;

public:
	RigidBodyGenerator(Vector3 org, int stNpart, RigidBodySystem* partsys, Scene* scn, double min = 20, double max = 30);
	virtual ~RigidBodyGenerator() = default;

	virtual void update(double t);
	virtual void generateParticles(double t) = 0;
	virtual bool mayGenerate() const { return nGameObjects <= maxGameObjects; }
	void addNumParticles(int n) { nGameObjects += n; }
	void generateParticle(Vector3 org, Vector3 vel, double life,
		Vector4 c = Vector4(1, 1, 1, 1), float mass = 1);

	/// setters
	void setOrigen(Vector3 o) { origen = o; }
	void setColor(const Vector4& c) { color = c; }
	void setColor(float r, float g,
		float b, float a) {
		color = Vector4(r, g, b, a);
	}
	void setScene(Scene* sc) { scene = sc; }
	void setMinLife(const double ml) { minLife = ml; }
	void setMaxLife(const double ml) { maxLife = ml; }
	void setMass(const float m) { mass = m; }
	void setSize(const float s) { size = s; }
	void setDampener(const double d) { dampener = d; }
	//void setVisibility(bool visibility);

	/// getters
	RigidBodySystem* getPartSyst() const { return system; }
	Vector3 getOrigen() const { return origen; }
	Vector4 getColor() const { return color; }
	Scene* getScene()	const { return scene; }
	double getMinLife() const { return minLife; }
	double getMaxLife() const { return maxLife; }
	float getMass() const { return mass; }
	float getSize() const { return size; }
	double getDampener() const { return dampener; }
	int getNumParticles() const { return nGameObjects; }
};
