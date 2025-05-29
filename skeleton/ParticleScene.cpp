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
	lowerThreshold = 10000;
	partSyst = new ParticleSystem(this); // inicialicacion de sistema
	addSystem(partSyst);

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

	//partSyst->addParticleGenerator(
	//	new MistGenerator(
	//		Vector3(-150, 0, -50),
	//		500,
	//		partSyst,
	//		this
	//	)
	//);

	// configuracion de generadores
	wg->setMinLife(10);
	wg->setMaxLife(20);
	rg->setMinLife(5);
	rg->setMaxLife(10);
	rg->setDampener(0.98);

	// asociacion sistema/generador
	partSyst->addParticleGenerator(wg);
	partSyst->addParticleGenerator(rg);
}

void ParticleScene::onDisable()
{
	Scene::onDisable();
}
