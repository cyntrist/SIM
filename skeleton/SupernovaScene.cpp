#include "SupernovaScene.h"

void SupernovaScene::setup()
{

}

void SupernovaScene::onEnable()
{
	Vector3 pos(-200, 5, -220);
	lowerThreshold = 10000;
	upperThreshold = 10000;


	Scene::onEnable();
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	auto partGen = new RandomMassGenerator(
		pos,
		3000,
		partSyst,
		this
	);
	partGen->setMinLife(10);
	partGen->setMaxLife(20);
	partGen->setColor(0,0,0,1);
	partGen->setSize(2, 15);
	partSyst->addParticleGenerator(partGen);

	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);

	auto whirlGen = new WhirlwindGenerator(pos, this);
	forceSyst->addForceGenerator(whirlGen);
	whirlGen->setRadius(250000);
	whirlGen->setClockwise(true);

	explosionGen = new ExplosionGenerator(pos, this);
	forceSyst->addForceGenerator(explosionGen);
	explosionGen->setRadius(250000);
	explosionGen->setPower(700);
}

void SupernovaScene::onDisable()
{
	Scene::onDisable();
}

void SupernovaScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		if (explosionGen != nullptr) explosionGen->startGenerating();
	default:
		break;
	}
}
