#include "ParticleGenerator.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include <algorithm>


ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn, 
	double min, double max)
	: origen(org), particleSystem(partsys), startNGameObjects(stNpart), scene(scn),
	minLife(min), maxLife(max)
{

}


void ParticleGenerator::update(double t)
{
	if (mayGenerate())
		generateParticles(t);
}


void ParticleGenerator::onGameObjectDeath(GameObject* p)
{

}

void ParticleGenerator::generateParticles(double t)
{
	Log("NUEVA PARTÍCULA");
}

void CascadaGen::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	uniform_int_distribution<> numPartsUniform(0, restParticles); 
	normal_distribution<> YnormalDistribution(20, 2.0); 
	normal_distribution<> ZnormalDistribution(10, 2.0); 
	normal_distribution<> ORGnormalDistribution(origen.x, 10.0); 
	uniform_real_distribution<> lifetimeDistr2(minLife, maxLife); 

	Vector3 origen2;
	Vector3 velocity(0,0,0); 
	int particlesGenerated = numPartsUniform(generator); 

	for (int i = 0; i < particlesGenerated; i++)
	{
		origen2 = origen;
		origen2.x = ORGnormalDistribution(generator);
		velocity.y = YnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		float maxLifetime = lifetimeDistr2(generator);
		maxLifetime = min(max(maxLifetime, 5.0f), 50.0f);

		auto aux = new Particle(scene, origen2, size);
		aux->setVel(velocity);
		//aux->setSize(size);
		aux->setMass(mass);
		aux->setMaxLifetime(maxLifetime);
		aux->toggleGrav();
		aux->setGenerator(this);
		aux->setColor(color);

		scene->addGameObject(aux); 

		nGameObjects++;
		nGameObjectsTotal++;
	}
}

void MistGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::uniform_int_distribution<> posXZUniform(-20, 20); 
	std::uniform_int_distribution<> posYUniform(0, 40); 
	std::normal_distribution<> Bdistribution(10, 0.8); 

	Vector3 origen2 = origen;
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);
		float lifetime = Bdistribution(generator);

		auto aux = new Particle(scene, origen2, size);
		aux->setVel(velocity);
		//aux->setSize(size);
		aux->setMaxLifetime(lifetime);
		aux->setGenerator(this);
		aux->setColor(color);

		scene->addGameObject(aux); 
		aux->toggleGrav();
		nGameObjects++;
		nGameObjectsTotal++;
	}
}

void RandomMassGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); 
	std::uniform_int_distribution<> posXZUniform(-20, 20); 
	std::uniform_int_distribution<> posYUniform(0, 50); 
	std::uniform_real_distribution<> lifeTimeUdistribution(minLife, maxLife); 
	std::normal_distribution<> massUdistribution(10, 3); 

	Vector3 origen2;
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		origen2 = origen;
		origen2.x += posXZUniform(generator);
		origen2.y += posYUniform(generator);
		origen2.z += posXZUniform(generator);

		float lifetime = lifeTimeUdistribution(generator);

		auto aux = new Particle(scene, origen2, size);
		aux->setVel(velocity);
		//aux->setSize(size);
		aux->setMaxLifetime(lifetime);
		aux->toggleGrav();
		aux->setMass(massUdistribution(generator));
		aux->setGenerator(this);
		aux->setColor(color);

		scene->addGameObject(aux); 
		nGameObjects++;
		nGameObjectsTotal++;
	}
}
