#include "ParticleGenerator.h"
#include "Scene.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn) :
	particleSystem(partsys), startNGameObjects(stNpart), origen(org)
{

}


void ParticleGenerator::update(double t)
{
	if (mayGenerate())
		generateParticle();
}


void ParticleGenerator::onGameObjectDeath(GameObject* p)
{

}

void ParticleGenerator::generateParticle()
{
	Log("NUEVA PARTÍCULA");
}

// --- GENERADOR DE CASCADA ---
void CascadaGen::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	// Generamos una cantidad de particulas, cuya cantidad entra en el rango de la capacidad de particulas maxima, es decir restParticles
	std::uniform_int_distribution<> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::normal_distribution<> YnormalDistribution(5, 2.0); // media|dispersion
	std::normal_distribution<> ZnormalDistribution(10, 2.0); // media|dispersion
	std::normal_distribution<> LFEnormalDistribution(2, 10.0); // media|dispersion
	std::normal_distribution<> ORGnormalDistribution(origen.x, 10.0); // media|dispersion

	Vector3 origen2; // origen de la nueva particula
	Vector3 velocity(0,0,0); // velocidad para la nueva particula
	float lifetime; // tiempo de vida para la nueva particula
	int particlesGenerated = numPartsUniform(generator); // cantidad de particulas que se van a generar

	for (int i = 0; i < particlesGenerated; i++)
	{
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = ORGnormalDistribution(generator);
		velocity.y = YnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		lifetime = LFEnormalDistribution(generator);

		// creamos la nueva particula
		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVel(velocity);
		aux->setSize(0.5);
		aux->setMaxLifetime(lifetime);
		aux->toggleGrav();

		// anadimos las particulas a la lista
		//generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux); // Aniadir a la escena y pasar referencia del generador

		//particles.push_back(aux);
		nGameObjects++;
		nGameObjectsTotal++;
	}
}


// --- GENERADOR DE NIEBLA ---
void NieblaGen::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<> posXZUniform(-20, 20); // numero de -10 a 10
	std::uniform_int_distribution<> posYUniform(0, 40); // numero de 0 a 20

	std::normal_distribution<> Bdistribution(10, 0.8); // numero de 0 a restParticles

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);

		lifetime = Bdistribution(generator);

		// creamos la nueva particula
		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVel(velocity);
		aux->setSize(0.25);
		aux->setMaxLifetime(lifetime);

		// añadimos las particulas a la lista
		//generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux); // Aniadir a la escena y pasar referencia del generador
		aux->toggleGrav();
		nGameObjects++;
		nGameObjectsTotal++;
	}
}

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
void RandomParticleGen::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	std::uniform_int_distribution<> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<> posXZUniform(-40, 40); // numero de -40 a 40
	std::uniform_int_distribution<> posYUniform(0, 80); // numero de 0 a 80

	std::uniform_real_distribution<> lifeTimeUdistribution(5, 10); // numero de 0 a restParticles
	std::normal_distribution<> massUdistribution(10, 0.2); // numero de 0 a restParticles

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++)
	{
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);

		lifetime = lifeTimeUdistribution(generator);

		// creamos la nueva particula
		auto aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVel(velocity);
		//aux->setSize(0.25);
		aux->setMaxLifetime(lifetime);
		aux->toggleGrav();
		aux->setMass(massUdistribution(generator));

		// añadimos las particulas a la lista
		//generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux); // Aniadir a la escena y pasar referencia del generador
		nGameObjects++;
		nGameObjectsTotal++;
	}
}
