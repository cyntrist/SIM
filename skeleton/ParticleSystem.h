#pragma once

#include <random>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Scene.h"

class ParticleSystem : public System
{
protected:
	std::vector<ParticleGenerator*> particleGenerators;

public:
	ParticleSystem(Scene* sc) : System(sc) { }

	~ParticleSystem() override
	{
		for (auto gen : particleGenerators)
			delete gen;
	};

	bool update(double t) override
	{
		for (auto gen : particleGenerators)
			gen->update(t);
		return true;
	}

	void addParticleGenerator(ParticleGenerator* gen)
	{
		particleGenerators.push_back(gen);
		gen->setScene(scene);
	}

	void destroyParticleGenerator(int i)
	{
		particleGenerators.erase(std::find(particleGenerators.begin(), particleGenerators.end(),
		                                   particleGenerators[i]));
	}
};

class FireworkSystem : public ParticleSystem
{
	default_random_engine generator;

	Particle* first = nullptr;
	FireworkGenerator* gen = nullptr;
	Vector3 origin, nextOrigin;
	Vector3 iniVel = {0, 60, 0};

public:
	FireworkSystem(Scene* scn, Vector3 orgn, Vector3 vel = {0, 40, 0})
	: ParticleSystem(scn), origin(orgn), nextOrigin(orgn), iniVel(vel), generator(69)
	{
		generateFirstPart();
	}

	~FireworkSystem() override
	{
		delete first;
		delete gen;
	}

	void setGenerator(FireworkGenerator* fw) { gen = fw; }

	void generateFirstPart()
	{
		if (first != nullptr)
		{
			delete first;
			return;
		}

		auto vel = iniVel;
		auto sigma = 10.0;
		normal_distribution<> xDist(0, sigma);
		normal_distribution<> yDist(0, sigma);
		normal_distribution<> zDist(0, sigma);
		vel.x += xDist(generator);
		vel.y += yDist(generator);
		vel.z += zDist(generator);

		first = new Particle(scene, origin, 2);
		first->setVel(vel);
		first->setMass(50);
		first->toggleGrav();
		first->setColor(Vector4(1,1,1,1));
	}

	bool update(double t) override
	{
		if (first == nullptr || !first->isAlive())
		{
			if (gen->getNumParticles() <= 1)
				generateFirstPart();
			return true;
		}

		if (first->isAlive() && first->getVel().y <= 0)
		{
			if (gen != nullptr && first != nullptr)
			{
				gen->setOrigen(nextOrigin);
				gen->generateParticles(t);
			}
			delete first;
			first = nullptr;
			return true;
		} 

		first->update(t);
		nextOrigin = first->getPosition();

		return true;
	};
};
