#include "WhirlScene.h"

void WhirlScene::setup()
{
	auto partsyst = new ParticleSystem(this);
	addSystem(partsyst);
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));

	auto fSys = new ForceSystem(this);
	addSystem(fSys);
	auto tgen = new WhirlwindGenerator({0, 0, 0}, this);
	fSys->addForceGenerator(tgen);
	tgen->setRadius(100);
}
