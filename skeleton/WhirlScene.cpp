#include "WhirlScene.h"

void WhirlScene::setup()
{

}

void WhirlScene::onEnable()
{
	Scene::onEnable();

	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	//partSyst->addParticleGenerator(
	//	new RandomMassGenerator(
	//		Vector3(-100, 0, -100), 
	//		1000,
	//		partSyst, 
	//		this
	//	)
	//);

	partSyst->addParticleGenerator(
		new RandomMassGenerator(
			Vector3(-100, 0, -100),
			1000,
			partSyst,
			this,
			30,
			60
		)
	);

	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);
	whirlGen = new WhirlwindGenerator({ -150, 0, -150 }, this);
	forceSyst->addForceGenerator(whirlGen);
	whirlGen->setRadius(250);
}

void WhirlScene::onDisable()
{
	Scene::onDisable();
}
