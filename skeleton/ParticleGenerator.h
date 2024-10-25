#pragma once
#include <random>

#include "Particle.h"

class ParticleGenerator : SceneObject
{
	Particle* model = nullptr; // particula modelo

	size_t num;
	size_t max_num; // max numero de particulas
	double min_life; // promedio vida
	double max_life; 
	std::vector<Particle*> particles; // vector de particulas

	Vector3 origin;
	Vector3 ini_speed;
	Vector3 mean_speed;

	double chance = 1; // probabilidad
	std::normal_distribution<> probability;
	std::random_device rd{};
	std::mt19937 mt{rd()};
public:
	ParticleGenerator();
	~ParticleGenerator() = default;
	bool update(double t) override;
	Particle* addParticle();
	bool shouldGenerate();
};

