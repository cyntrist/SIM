#include "ParticleGenerator.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include <algorithm>


ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn,
                                     double min, double max)
	: origen(org), particleSystem(partsys), maxGameObjects(stNpart), scene(scn),
	  minLife(min), maxLife(max)
{
}


void ParticleGenerator::update(double t)
{
	if (mayGenerate())
		generateParticles(t);
}

Particle* ParticleGenerator::generateParticle(Vector3 org, Vector3 vel, double life, Vector4 c, float m)
{
	auto aux = new Particle(scene, org, size);
	aux->setVel(vel);
	aux->setMaxLifetime(life);
	aux->toggleGrav();
	aux->setMass(m);
	aux->setGenerator(this);
	if (color != Vector4(1, 1, 1, 1))
		aux->setColor(color);
	aux->setDamp(dampener);

	scene->addGameObject(aux);
	addNumParticles(1);
	nGameObjectsTotal++;

	return aux;
}

void ParticleGenerator::generateParticles(double t)
{
}


/// <summary>
/// CATARATA
/// </summary>
/// <param name="t"></param>
void WaterfallGenerator::generateParticles(double t)
{
	int restParticles = maxGameObjects / 2 - nGameObjects;

	uniform_int_distribution<> numPartsUniform(0, restParticles);
	normal_distribution<> YnormalDistribution(20, 2.0);
	normal_distribution<> ZnormalDistribution(10, 2.0);
	normal_distribution<> ORGnormalDistribution(origen.x, 10.0);
	uniform_real_distribution<> lifetimeDistr2(minLife, maxLife);

	Vector3 org;
	Vector3 vel(0, 0, 0);
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		org = origen;
		org.x = ORGnormalDistribution(generator);
		vel.y = YnormalDistribution(generator);
		vel.z = ZnormalDistribution(generator);
		float maxLifetime = lifetimeDistr2(generator);
		maxLifetime = min(max(maxLifetime, 5.0f), 50.0f);

		generateParticle(org, vel, maxLifetime, color, mass);
	}
}

/// <summary>
/// NEBLINA
/// </summary>
/// <param name="t"></param>
void MistGenerator::generateParticles(double t)
{
	int restParticles = maxGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::uniform_int_distribution<> posXZUniform(-20, 20);
	std::uniform_int_distribution<> posYUniform(0, 40);
	std::normal_distribution<> Bdistribution(10, 0.8);

	Vector3 vel(0, 0, 0);
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		Vector3 org;
		org.x = posXZUniform(generator);
		org.y = posYUniform(generator);
		org.z = posXZUniform(generator);
		float lifetime = Bdistribution(generator);

		generateParticle(org, vel, lifetime, color, mass);
	}
}

/// MASAS ALEATORIAS
/// @param t 
void RandomMassGenerator::generateParticles(double t)
{
	int restParticles = maxGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::normal_distribution<> posXZUniform(0, 20);
	std::normal_distribution<> posYUniform(0, 20);
	std::uniform_real_distribution<> lifeTimeUdistribution(minLife, maxLife);
	std::uniform_real_distribution<> sizeDistribution(minSize, maxSize);
	double size = sizeDistribution(generator);
	std::normal_distribution<> massUdistribution(10, 3);

	Vector3 org;
	Vector3 vel(0, 0, 0);
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		org = origen;
		org.x += posXZUniform(generator);
		org.y += posYUniform(generator);
		org.z += posXZUniform(generator);

		float lifetime = lifeTimeUdistribution(generator);

		auto aux = new Particle(scene, org, size);
		aux->setVel(vel);
		aux->setMaxLifetime(lifetime);
		aux->toggleGrav();
		aux->setMass(size);
		aux->setGenerator(this);
		aux->setColor(color);
		aux->setDamp(dampener);

		scene->addGameObject(aux);
		nGameObjects++;
		nGameObjectsTotal++;
	}
}

/// <summary>
/// MASAS FIJAS
/// </summary>
/// <param name="t"></param>
void EqualMassGenerator::generateParticles(double t)
{
	int restParticles = maxGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::normal_distribution<> posXZUniform(0, 20);
	std::normal_distribution<> posYUniform(0, 20);
	std::uniform_real_distribution<> lifeTimeUdistribution(minLife, maxLife);

	Vector3 org;
	Vector3 vel(0, 0, 0);
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		uniform_real_distribution<> rGen(0.5f, 1.1f);
		uniform_real_distribution<> gGen(0.5f, 1.1f);
		uniform_real_distribution<> bGen(0.5f, 1.1f);
		float r = rGen(generator);
		float g = gGen(generator);
		float b = bGen(generator);
		color = {r, g, b, 1.0};

		org = origen;
		org.x += posXZUniform(generator);
		org.y += posYUniform(generator);
		org.z += posXZUniform(generator);

		float lifetime = lifeTimeUdistribution(generator);

		generateParticle(org, vel, lifetime, color, mass);
	}
}


/// FUEGO ARTIFICIAL
void FireworkGenerator::generateParticles(double t)
{
	int restParticles = maxGameObjects / 2 - nGameObjects;

	uniform_int_distribution<> numPartsUniform(0, restParticles);
	auto sigma = 20.0;
	normal_distribution<> xDist(0, sigma);
	normal_distribution<> yDist(0, sigma);
	normal_distribution<> zDist(0, sigma);
	uniform_real_distribution<> lifeDist(minLife, maxLife);

	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		// MASAS
		std::uniform_real_distribution<> sizeDistribution(0.5, 2);
		double s = sizeDistribution(generator);

		//COLORES
		//uniform_real_distribution<> rGen(0.2f, 1.01f);
		//uniform_real_distribution<> gGen(0.2f, 1.01f);
		//uniform_real_distribution<> bGen(0.2f, 1.01f);
		normal_distribution<> rGen(0.5f, 0.3f);
		normal_distribution<> gGen(0.5f, 0.3f);
		normal_distribution<> bGen(0.5f, 0.3f);
		float r = rGen(generator);
		float g = gGen(generator);
		float b = bGen(generator);
		color = { r, g, b, 1.0 };

		// VELOCIDAD
		Vector3 vel;
		vel.x = xDist(generator);
		vel.y = yDist(generator);
		vel.z = zDist(generator);
		if (bidim)
		{
			//if (par)
				vel.z = 0;
			//else
				//vel.x = 0;
			//par = !par;
		}

		// TIEMPO DE VIDA
		float maxLifetime = lifeDist(generator);
		maxLifetime = min(max(maxLifetime, 5.0f), 50.0f);

		size = s;
		generateParticle(origen, vel, maxLifetime, color, s);
	}
}

void FireworkGenerator::update(double t)
{
}

bool FireworkGenerator::mayGenerate() const
{
	return true;
}

void CircleGenerator::generateParticles(double t)
{
	constexpr int radius = 30;
	actAngle += angStep;

	//POSICION Y VELOCIDAD
	auto cos = PxCos(actAngle), sen = PxSin(actAngle);
	Vector3 pos = { radius * cos, radius * sen, 0 };
	Vector3 vel = { 25 * cos, 25 * sen, 0 };
	//(radius * Math::Cos(inc * i), radius * Math::Sin(inc * i), 0)

	//COLORES
	//Log(to_string(hsvColor));
	if (hsvColor >= 30)
		sentido = -1;
	if (hsvColor <= 0)
		sentido = 1;
	hsvColor = hsvColor + angStep * sentido;
	color = hsvToRgb(hsvColor * 10);

	auto aux = generateParticle(origen + pos, vel, maxLife, color, mass);
	aux->toggleGrav();
}

void CircleGenerator::update(double t)
{
	if (mayGenerate())
		generateParticles(t);
}

bool CircleGenerator::mayGenerate()
{
	if (nGameObjects >= maxGameObjects)
		return false;
	counter += 1;
	if (counter >= timer)
	{
		counter = 0;
		return true;
	}
	return false;
}
















