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
	Scene::onEnable();
	partSyst = new ParticleSystem(this);
	addSystem(partSyst);
	partSyst->addParticleGenerator(new CascadaGen(Vector3(0, 50, 0), 100, partSyst, this));

	//forceSyst = new ForceSystem(this);
	//addSystem(forceSyst);
	//windGen = new WindGenerator({ 0,0,0 }, this, { 5,0,0 });
	//forceSyst->addForceGenerator(windGen);
	//windGen->setRadius(20);
}

void ParticleScene::onDisable()
{
	Scene::onDisable();
}
