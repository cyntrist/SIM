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

void ParticleGenerator::onGameObjectDeath(GameObject* p) { }
void ParticleGenerator::generateParticles(double t) { }


/// <summary>
/// CATARATA
/// </summary>
/// <param name="t"></param>
void WaterfallGenerator::generateParticles(double t)
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
		aux->setDamp(dampener);

		scene->addGameObject(aux); 

		nGameObjects++;
		nGameObjectsTotal++;
	}
}

/// <summary>
/// NEBLINA
/// </summary>
/// <param name="t"></param>
void MistGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::uniform_int_distribution<> posXZUniform(-20, 20); 
	std::uniform_int_distribution<> posYUniform(0, 40); 
	std::normal_distribution<> Bdistribution(10, 0.8); 

	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		Vector3 org;
		org.x = posXZUniform(generator);
		org.y = posYUniform(generator);
		org.z = posXZUniform(generator);
		float lifetime = Bdistribution(generator);

		auto aux = new Particle(scene, org, size);
		aux->setVel(velocity);
		//aux->setSize(size);
		aux->setMaxLifetime(lifetime);
		aux->setGenerator(this);
		aux->setColor(color);
		aux->setDamp(dampener);

		scene->addGameObject(aux); 
		aux->toggleGrav();
		nGameObjects++;
		nGameObjectsTotal++;
	}
}

/// MASAS ALEATORIAS
/// @param t 
void RandomMassGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); 
	std::normal_distribution<> posXZUniform(0, 20); 
	std::normal_distribution<> posYUniform(0, 20);
	std::uniform_real_distribution<> lifeTimeUdistribution(minLife, maxLife); 
	std::uniform_real_distribution<> sizeDistribution(minSize,maxSize);
	double size = sizeDistribution(generator);
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
	int restParticles = startNGameObjects / 2 - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles);
	std::normal_distribution<> posXZUniform(0, 20);
	std::normal_distribution<> posYUniform(0, 20);
	std::uniform_real_distribution<> lifeTimeUdistribution(minLife, maxLife);

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


/// FUEGO ARTIFICIAL
void FireworkGenerator::generateParticles(double t)
{
	int restParticles = startNGameObjects / 2 - nGameObjects;

	uniform_int_distribution<> numPartsUniform(0, restParticles);
	normal_distribution<> YnormalDistribution(20, 2.0);
	normal_distribution<> ZnormalDistribution(10, 2.0);
	normal_distribution<> ORGnormalDistribution(origen.x, 10.0);
	uniform_real_distribution<> lifetimeDistr2(minLife, maxLife);

	Vector3 origen2;
	Vector3 velocity(0, 0, 0);
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		uniform_real_distribution<> rGen(0.0f, 1.0f);
		uniform_real_distribution<> gGen(0.0f, 1.0f);
		uniform_real_distribution<> bGen(0.0f, 1.0f);
		float r = rGen(generator);
		float g = gGen(generator);
		float b = bGen(generator);

		color = {r, g, b, 1.0 };

		origen2 = origen;
		origen2.x = ORGnormalDistribution(generator);
		velocity.y = YnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		float maxLifetime = lifetimeDistr2(generator);
		maxLifetime = min(max(maxLifetime, 5.0f), 50.0f);

		auto aux = new Particle(scene, origen2, size);
		aux->setVel(velocity);
		aux->setMass(mass);
		aux->setMaxLifetime(maxLifetime);
		aux->toggleGrav();
		aux->setGenerator(this);
		aux->setColor(color);
		aux->setDamp(dampener);

		scene->addGameObject(aux);

		nGameObjects++;
		nGameObjectsTotal++;
	}
}

void FireworkGenerator::update(double t)
{
	
}

bool FireworkGenerator::mayGenerate() const
{
	return true;
}


