#pragma once
#include <random>

#include "Particle.h"
#include "Scene.h"

enum class Mode
{
	FUENTE,
	FUEGOS,
	HUMO
};

class ParticleGenerator
{
	Mode modo = Mode::FUENTE;
	Scene* scene = nullptr;
	Particle* model = nullptr; // particula modelo

	size_t num = 0;
	size_t max_num; // max numero de particulas
	double min_life; // promedio vida
	double max_life;
	std::vector<Particle*> particles; // vector de particulas

	Vector3 origin;
	Vector3 ini_speed;
	Vector3 mean_speed;

	double chance = 1; // probabilidad
	std::normal_distribution<> probability();
	std::random_device rd{};
	std::mt19937 mt{rd()};

public:
	ParticleGenerator(Particle* model, Mode mode = Mode::FUENTE);
	ParticleGenerator(Vector3 origin, Vector3 speed, double max_life, Mode mode = Mode::FUENTE);
	~ParticleGenerator() = default;
	bool update(double t);
	Particle* addParticle();
	bool shouldGenerate();
	void setMode(const Mode m) { modo = m; }
	void setScene(Scene* s) { scene = s; }
};
