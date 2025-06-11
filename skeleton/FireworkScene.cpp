#include "FireworkScene.h"

#include "ParticleSystem.h"
#include "SceneManager.h"

void FireworkScene::onEnable()
{
	Scene::onEnable(); // inicialización de escena
	sm->setGameWon(true);

	lowerThreshold = 500;
	upperThreshold = 400;

	//partSyst = new ParticleSystem(this); // inicialicacion de sistema
	//addSystem(partSyst);
	//auto wg = new WaterfallGenerator(
	//	Vector3(-50, 50, -50),
	//	750,
	//	partSyst,
	//	this
	//);
	//wg->setMinLife(5);
	//wg->setMaxLife(15);
	//partSyst->addParticleGenerator(wg);

	float x = 100, y = -30, z = 100;
	PxVec3 vel = { 0, 50, 0 };
	firewSyst1 = new FireworkSystem(
		this, 
		Vector3(x, y, z),
		vel,
		69
	); // inicialicacion de sistema
	auto fw1 = new FireworkGenerator(
		1000,
		firewSyst1,
		this
	);
	fw1->setMinLife(1);
	fw1->setMaxLife(4);
	addSystem(firewSyst1);
	firewSyst1->setGenerator(fw1);

	firewSyst2 = new FireworkSystem(
		this, 
		Vector3(-x, y, z), 
		vel,
		420
	); // inicialicacion de sistema
	auto fw2 = new FireworkGenerator(
		1000,
		firewSyst2,
		this
	);
	fw2->setMinLife(2);
	fw2->setMaxLife(3);
	addSystem(firewSyst2);
	firewSyst2->setGenerator(fw2);

}

void FireworkScene::onDisable()
{
	Scene::onDisable();
}
