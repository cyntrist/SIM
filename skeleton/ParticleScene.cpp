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
			500, 
			partSyst, 
			this
		)
	);

	partSyst->addParticleGenerator(
		new MistGenerator(
			Vector3(-150, 0, -50),
			500,
			partSyst,
			this
		)
	);

	partSyst->addParticleGenerator(
		new RandomParticleGen(
			Vector3(-200, 0, 0),
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
