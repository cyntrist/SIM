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
	partSyst->addParticleGenerator(
		new CascadaGen(
			Vector3(-50, 50, -50), 
			1000, 
			partSyst, 
			this
		)
	);
}

void ParticleScene::onDisable()
{
	Scene::onDisable();
}
