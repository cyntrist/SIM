#include "ParticleGenerator.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include <algorithm>


ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn) :
	particleSystem(partsys), startNGameObjects(stNpart), origen(org), scene(scn)
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

// --- GENERADOR DE CASCADA ---
void CascadaGen::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	uniform_int_distribution<> numPartsUniform(0, restParticles); 
	normal_distribution<> YnormalDistribution(20, 2.0); 
	normal_distribution<> ZnormalDistribution(10, 2.0); 
	normal_distribution<> ORGnormalDistribution(origen.x, 10.0); 
	uniform_real_distribution<> lifetimeDistr2(5, 30); 

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

		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2, 3);
		aux->setVel(velocity);
		aux->setSize(15);
		aux->setMass(5);
		aux->setMaxLifetime(maxLifetime);
		aux->toggleGrav();
		aux->setGenerator(this);
		aux->setColor(0.5, 0.5, 0.9, 1);

		scene->addGameObject(aux); 

		nGameObjects++;
		nGameObjectsTotal++;
	}
}


// --- GENERADOR DE NIEBLA ---
void MistGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<> posXZUniform(-20, 20); // numero de -10 a 10
	std::uniform_int_distribution<> posYUniform(0, 40); // numero de 0 a 20
	std::normal_distribution<> Bdistribution(10, 0.8); // numero de 0 a restParticles

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

		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVel(velocity);
		aux->setSize(5);
		aux->setMaxLifetime(lifetime);
		aux->setGenerator(this);
		aux->setColor(0.5, 0.7, 0.3, 1);

		scene->addGameObject(aux); 
		aux->toggleGrav();
		nGameObjects++;
		nGameObjectsTotal++;
	}
}

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
void RandomParticleGen::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<> posXZUniform(-20, 20); // numero de -40 a 40
	std::uniform_int_distribution<> posYUniform(0, 50); // numero de 0 a 80
	std::uniform_real_distribution<> lifeTimeUdistribution(20, 30); // numero de 0 a restParticles
	std::normal_distribution<> massUdistribution(10, 3); // numero de 0 a restParticles

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

		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVel(velocity);
		aux->setSize(0.1);
		aux->setMaxLifetime(lifetime);
		aux->toggleGrav();
		aux->setMass(massUdistribution(generator));
		aux->setGenerator(this);
		aux->setColor(0.9, 0.7, 0.2, 1);

		scene->addGameObject(aux); 
		nGameObjects++;
		nGameObjectsTotal++;
	}
}
