#include "WindScene.h"

void WindScene::setup()
{

}

void WindScene::onEnable()
{
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	partSyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 300, partSyst, this));


	//forceSyst = new ForceSystem(this);
	//addSystem(forceSyst);
	//windGen = new WindGenerator({ 0, 0, 0 }, this, { 0, 0, 0 });
	//forceSyst->addForceGenerator(windGen);
	//windGen->setRadius(100);
}

void WindScene::onDisable()
{
	Scene::onDisable();
}
