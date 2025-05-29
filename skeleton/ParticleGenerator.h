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

	Vector3 origen;
	Vector4 color = Vector4(1,1,1,1);
	Scene* scene;
	int startNGameObjects;
	int nGameObjects = 0;
	int nGameObjectsTotal = 0;
	double minLife, maxLife;
	float mass = 1, size = 5;
	double dampener = 0.98;

public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30);
	virtual ~ParticleGenerator() = default;

	void update(double t);
	virtual void generateParticles(double t) = 0;
	bool mayGenerate() const			{ return nGameObjects <= startNGameObjects; }
	void addNumParticles(int n)			{ nGameObjects += n;  }
	void onGameObjectDeath(GameObject* p);

	/// setters
	void setOrigen(const Vector3& o)	{ origen = o; }
	void setColor(const Vector4& c)		{ color = c; }
	void setColor(float r, float g, 
		float b, float a)				{ color = Vector4(r,g,b,a); }
	void setScene(Scene* sc)			{ scene = sc; }
	void setMinLife(const double ml)	{ minLife = ml; }
	void setMaxLife(const double ml)	{ maxLife = ml; }
	void setMass(const float m)			{ mass = m; }
	void setSize(const float s)			{ size = s; }
	void setDampener(const double d)	{ dampener = d; }
	//void setVisibility(bool visibility);

	/// getters
	ParticleSystem* getPartSyst() const { return particleSystem; }
	Vector3 getOrigen() const			{ return origen; }
	Vector4 getColor() const			{ return color; }
	Scene* getScene()	const			{ return scene; }
	double getMinLife() const			{ return minLife; }
	double getMaxLife() const			{ return maxLife; }
	float getMass() const				{ return mass; }
	float getSize() const				{ return size; }
	double getDampener() const			{ return dampener; }
	int getNumParticles() const			{ return nGameObjects; }
};

class WaterfallGenerator : public ParticleGenerator
{
public:
	WaterfallGenerator(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
	: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4(0,0,1,1);
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
		color = Vector4(0,1,0,1);
		size = 4;
	}

	void generateParticles(double t) override;
};

class RandomMassGenerator : public ParticleGenerator // 
{
	float minSize = 2;
	float maxSize = 6;

public:
	RandomMassGenerator(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
	: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4(1,0,0,1);
	}
	void generateParticles(double t) override;
	void setSize(float min, float max) { minSize = min; maxSize = max; }
};

class EqualMassGenerator : public ParticleGenerator // 
{
public:
	EqualMassGenerator(Vector3 org, int nparts, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30)
		: ParticleGenerator(org, nparts, partsys, scn, min, max)
	{
		color = Vector4(1, 1, 0, 1);
	}
	void generateParticles(double t) override;
};
