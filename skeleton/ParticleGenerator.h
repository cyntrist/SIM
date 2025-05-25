#pragma once
#include "Particle.h"
#include <random>

class ParticleSystem;
class Scene;

constexpr double MIN_TIMER = 0.0001;

class ParticleGenerator
{
protected:
	default_random_engine generator;
	ParticleSystem* particleSystem;

	// Propiedades inicio
	Vector3 origen;
	Vector3 startVel;
	float startLifetime;

	float startSize;
	Vector4 startColor;

	// Current particles
	Scene* scene;
	int startNGameObjects;
	int nGameObjects = 0;
	int nGameObjectsTotal = 0;
	double minLife, maxLife;
	float mass = 1, size = 5;
	Vector4 color = Vector4(1,1,1,1);

public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30);
	virtual ~ParticleGenerator() = default;

	void update(double t);
	void setScene(Scene* sc) { scene = sc; }

	virtual void generateParticles(double t) = 0;
	bool mayGenerate() const { return nGameObjects <= startNGameObjects; }

	int getNumParticles() const { return nGameObjects; }
	void addNumParticles(int n) { nGameObjects += n;  }
	void onGameObjectDeath(GameObject* p);

	//void setVisibility(bool visibility);
};

class CascadaGen : public ParticleGenerator
{
public:
	CascadaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
	: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4();
		size = 2;
	}

	void generateParticles(double t) override;
};

class MistGenerator : public ParticleGenerator
{
public:
	MistGenerator(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
		: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4();
		size = 4;
	};

	void generateParticles(double t) override;
};

class RandomMassGenerator : public ParticleGenerator // 
{
public:
	RandomMassGenerator(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
	: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4();
	}
	void generateParticles(double t) override;
};
