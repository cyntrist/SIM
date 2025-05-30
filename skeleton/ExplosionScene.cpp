#include "ExplosionScene.h"

void ExplosionScene::setup()
{

}

void ExplosionScene::onEnable()
{
	Vector3 pos(-200, 0, -200);
	lowerThreshold = 1000000;
	upperThreshold = 1000000;


	Scene::onEnable();
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	auto partGen = new RandomMassGenerator(
		pos,
		1000,
		partSyst,
		this
	);
	partGen->setMinLife(10);
	partGen->setMaxLife(20);
	partSyst->addParticleGenerator(partGen);


	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);

	auto whirlGen = new WhirlwindGenerator(pos, this);
	forceSyst->addForceGenerator(whirlGen);
	whirlGen->setRadius(250000);

	explosionGen = new ExplosionGenerator(pos, this);
	forceSyst->addForceGenerator(explosionGen);
	explosionGen->setRadius(250000);
	explosionGen->setPower(500);
}

void ExplosionScene::onDisable()
{
	Scene::onDisable();
}

void ExplosionScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		if (explosionGen != nullptr) explosionGen->startGenerating();
	default:
		break;
	}
}
