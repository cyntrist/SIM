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
	Particle* first = nullptr;
	FireworkGenerator* gen = nullptr;
	Vector3 origin;
	Vector3 firstVel = {0, 40, 0};

public:
	FireworkSystem(Scene* scn, Vector3 orgn) : ParticleSystem(scn), origin(orgn)
	{
		generateFirstPart();
	}

	~FireworkSystem() override
	{
		delete first;
		delete gen;
	}

	void setGen(FireworkGenerator* fw) { gen = fw; }

	void generateFirstPart()
	{
		if (first != nullptr)
		{
			first->kill();
			return;
		}

		first = new Particle(scene, origin, 2);
		first->setVel(firstVel);
		first->setMass(0.5);
		first->toggleGrav();
		first->setColor(Vector4(1,1,1,1));
		//first->setGenerator(gen);

		scene->addGameObject(first);
	}

	bool update(double t) override
	{
		if (first == nullptr || !first->isAlive())
		{
			generateFirstPart();
			return true;
		}

		if (first->getVel().y <= 0)
		{
			first->kill();
			if (gen != nullptr)
				gen->generateParticles(t);
			return true;
		} 

		first->update(t);

		return true;
	};
};
