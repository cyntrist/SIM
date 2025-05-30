#include "ParticleScene.h"

#include "ForceSystem.h"
#include "ParticleSystem.h"

ParticleScene::ParticleScene(Camera* cam) : Scene(cam)
{
}

void ParticleScene::setup()
{

}

void ParticleScene::onEnable()
{
	Scene::onEnable(); // inicialización de escena
	lowerThreshold = 400;
	upperThreshold = 400;
	partSyst = new ParticleSystem(this); // inicialicacion de sistema
	firewSyst = new FireworkSystem(this, Vector3(20,0,-80)); // inicialicacion de sistema
	addSystem(partSyst);
	addSystem(firewSyst);

	// inicialicacion de generadores
	auto wg = new WaterfallGenerator(
		Vector3(-50, 50, -50),
		750,
		partSyst,
		this
	);
	auto rg = new RandomMassGenerator(
		Vector3(-200, 0, 0),
		1000,
		partSyst,
		this
	);

	auto fw = new FireworkGenerator(
		1000,
		firewSyst,
		this
	);

	// configuracion de generadores
	wg->setMinLife(10);
	wg->setMaxLife(20);
	rg->setMinLife(5);
	rg->setMaxLife(10);
	rg->setDampener(0.98);

	// asociacion sistema/generador
	partSyst->addParticleGenerator(wg);
	partSyst->addParticleGenerator(rg);
	firewSyst->setGen(fw);
}

void ParticleScene::onDisable()
{
	Scene::onDisable();
}
