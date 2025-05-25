#include "ExplosionScene.h"

void ExplosionScene::setup()
{
	auto partsyst = new ParticleSystem(this);
	addSystem(partsyst);
	partsyst->addParticleGenerator(new RandomMassGenerator(Vector3(0, 0, 0), 1000, partsyst, this));


	auto fSys = new ForceSystem(this);
	addSystem(fSys);
	auto egen = new ExplosionGenerator({ 0,0,0 }, this);
	fSys->addForceGenerator(egen);
	egen->setRadius(50);
	explosionGen = egen;
}

void ExplosionScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		explosionGen->startGenerate();
	default:
		break;
	}
}
