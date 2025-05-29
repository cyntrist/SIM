#include "WhirlScene.h"

void WhirlScene::setup()
{

}

void WhirlScene::onEnable()
{
	Scene::onEnable();

	Vector3 pos(-300, 0, -300);

	/// PARTICULAS
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);

	auto rg = new EqualMassGenerator(
		pos,
		1000,
		partSyst,
		this,
		30,
		60
	);

	rg->setMinLife(20);
	rg->setMaxLife(30);
	rg->setMass(3);

	partSyst->addParticleGenerator(rg);


	/// FUERZAS
	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);
	whirlGen = new WhirlwindGenerator(pos, this);
	forceSyst->addForceGenerator(whirlGen);
	whirlGen->setRadius(250000000);
}

void WhirlScene::onDisable()
{
	Scene::onDisable();
}
