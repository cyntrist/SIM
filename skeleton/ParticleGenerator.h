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
	int maxGameObjects;
	int nGameObjects = 0;
	int nGameObjectsTotal = 0;
	double minLife, maxLife;
	float mass = 1, size = 5;
	double dampener = 0.98;

public:
	ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn, double min = 20, double max = 30);
	virtual ~ParticleGenerator() = default;

	virtual void update(double t);
	virtual void generateParticles(double t) = 0;
	virtual bool mayGenerate() const	{ return nGameObjects <= maxGameObjects; }
	void addNumParticles(int n)			{ nGameObjects += n;  }
	void generateParticle(Vector3 org, Vector3 vel, double life, 
		Vector4 c = Vector4(1, 1, 1, 1), float mass = 1);

	/// setters
	void setOrigen(Vector3 o)			{ origen = o; }
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

class FireworkGenerator : public ParticleGenerator // 
{
	bool bidim = false; // si es bidimensional
	bool par = false; // para ir cambiando de dimension alternadamente

public:
	FireworkGenerator( int nparts, ParticleSystem* partsys, Scene* scn, bool bi = false, double min = 20, double max = 30)
		: ParticleGenerator(Vector3(0,0,0), nparts, partsys, scn, min, max), bidim(bi)
	{
		color = Vector4(0, 1, 0, 1);
		size = 0.5;
	}

	void generateParticles(double t) override;
	void update(double t) override;
	bool mayGenerate() const override;
};
