#pragma once
#include "Particle.h"
#include <random>

class ParticleSystem;
class Scene;

class ParticleGenerator
{
protected:
	default_random_engine generator;
	ParticleSystem* particleSystem;

	// Propiedades inicio
	int startNGameObjects;
	Vector3 origen;
	Vector3 startVel;
	float startLifetime;

	float startSize;
	Vector4 startColor;

	// Current particles
	Scene* scene;
	int nGameObjects = 0;
	int nGameObjectsTotal = 0;

public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn);
	virtual ~ParticleGenerator() = default;

	void update(double t);
	void setScene(Scene* sc) { scene = sc; }

	virtual void generateParticle() = 0;
	bool mayGenerate() const { return nGameObjects <= startNGameObjects; }

	int getNumParticles() const { return nGameObjects; }
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

	void generateParticle() override;
};

// --- GENERADOR DE NIEBLA ---
class NieblaGen : public ParticleGenerator
{
public:
	NieblaGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(
		org, nparts, partsys, scn) {}

	~NieblaGen() {}

	void generateParticle() override;
};

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
class RandomParticleGen : public ParticleGenerator
{
public:
	RandomParticleGen(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn) : ParticleGenerator(
		org, nparts, partsys, scn) {}

	~RandomParticleGen() {}

	void generateParticle() override;
};
