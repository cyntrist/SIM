#include "WindScene.h"

void WindScene::setup()
{

}

void WindScene::onEnable()
{
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);

	partGen = new RandomMassGenerator(Vector3(-100, 50, -100), 300, partSyst, this);
	partSyst->addParticleGenerator(partGen);
	

	forceSyst = new ForceSystem(this);
	addSystem(forceSyst);
	auto windGen = new WindGenerator({ -100,0,-100 }, this, { 25,0,0 });
	forceSyst->addForceGenerator(windGen);
	windGen->setRadius(50);
}

void WindScene::onDisable()
{
	Scene::onDisable();
}
