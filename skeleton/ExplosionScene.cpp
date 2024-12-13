#include "ExplosionScene.h"

void ExplosionScene::setup()
{
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));


	ForceSystem* fSys = new ForceSystem(this);
	addSystem(fSys);
	ExplosionGenerator* egen = new ExplosionGenerator({ 0,0,0 }, this);
	fSys->addForceGenerator(egen);
	egen->setRadius(50);
	explosionGen = egen;
}

void ExplosionScene::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		explosionGen->startGenerate();
	default:
		break;
	}
}
