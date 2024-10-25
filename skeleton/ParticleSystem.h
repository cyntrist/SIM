#pragma once

#include <random>
#include <vector>
#include "Particle.h"

class ParticleSystem
{
	Particle* model = nullptr; // particula modelo
	size_t max_num; // max numero de particulas
	double min_life; // promedio vida
	double max_life; 
	std::vector<Particle*> particles; // vector de particulas
	Vector3 origin;
	Vector3 ini_speed;
	Vector3 mean_speed;
	double chance = 1; // probabilidad
	std::uniform_real_distribution<> probability;
	std::random_device rd{};
	std::mt19937 mt{rd()};


public:
	ParticleSystem() = default;
	~ParticleSystem()  = default;

	bool update(double t);
	void addParticle();
	void destroyParticle();
};

