#include "ExplosionScene.h"

void ExplosionScene::setup()
{

}

void ExplosionScene::onEnable()
{
	Scene::onEnable();
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	partSyst->addParticleGenerator(
		new RandomMassGenerator(
			Vector3(0, 0, 0), 
			1000, 
			partSyst,
			this
		)
	);


	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);
	explosionGen = new ExplosionGenerator({ 0,0,0 }, this);
	forceSyst->addForceGenerator(explosionGen);
	explosionGen->setRadius(50);
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
