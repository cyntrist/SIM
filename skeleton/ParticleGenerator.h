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

public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn);
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

// --- GENERADOR DE CASCADA ---
class CascadaGen : public ParticleGenerator
{
public:
	CascadaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(
		org, nparts, partsys, scn) {}

	~CascadaGen() {}

	void generateParticles(double t) override;
};

// --- GENERADOR DE NIEBLA ---
class NieblaGen : public ParticleGenerator
{
public:
	NieblaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(
		org, nparts, partsys, scn) {}

	~NieblaGen() {}

	void generateParticles(double t) override;
};

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
class RandomParticleGen : public ParticleGenerator
{
public:
	RandomParticleGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(
		org, nparts, partsys, scn) {}

	~RandomParticleGen() {}

	void generateParticles(double t) override;
};
