#pragma once
#include <random>
#include "RigidBody.h"

class Level;
class RigidBodySystem;

class RigidBodyGenerator
{
	Scene* scene;
	Level* level;
	PxPhysics* gphys;
	PxScene* gscn;
	RigidBodySystem* system;
	std::default_random_engine generator;

	Vector3 origen = {0, 0, 0};
	Vector3 velocity = Vector3(-12, 12, 0);
	Vector4 color = Vector4(1, 1, 1, 1);
	int maxGameObjects = 100;
	int nGameObjects = 0;
	float density = -1;
	double minLife, maxLife;
	float mass = 1, size = 1;
	double counter = 0, timer = 100;
	bool sw = false;

public:
	RigidBodyGenerator(Vector3 org, int stNpart, PxPhysics* gphys, PxScene* gscn, 
	                   RigidBodySystem* partsys, Level* scn, 
	                   double min = 20, double max = 30,
	                   double freq = 100);
	virtual ~RigidBodyGenerator() = default;

	virtual void update(double t);
	virtual void generateBody(double t);
	virtual bool mayGenerate();
	void addNumBodies(int n) { nGameObjects += n; }
	//void generateBody(Vector3 org, Vector3 vel, double life,
	//                      Vector4 c = Vector4(1, 1, 1, 1), float mass = 1);
	void setDummy();

	/// setters
	void setOrigen(Vector3 o) { origen = o; }
	void setColor(const Vector4& c) { color = c; }

	void setColor(float r, float g,
	              float b, float a)
	{
		color = Vector4(r, g, b, a);
	}

	void setScene(Scene* sc) { scene = sc; }
	void setMinLife(const double ml) { minLife = ml; }
	void setMaxLife(const double ml) { maxLife = ml; }
	void setMass(const float m) { mass = m; }
	void setSize(const float s) { size = s; }
	//void setVisibility(bool visibility);

	/// getters
	RigidBodySystem* getRBSystem() const { return system; }
	Vector3 getOrigen() const { return origen; }
	Vector4 getColor() const { return color; }
	Scene* getScene() const { return scene; }
	double getMinLife() const { return minLife; }
	double getMaxLife() const { return maxLife; }
	float getMass() const { return mass; }
	float getSize() const { return size; }
	int getNumBodies() const { return nGameObjects; }
};
