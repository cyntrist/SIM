#include "WindScene.h"

void WindScene::setup()
{
	auto partsyst = new ParticleSystem(this);
	addSystem(partsyst);
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));


	auto fSys = new ForceSystem(this);
	addSystem(fSys);
	auto vgen = new VientoGenerador({0, 0, 0}, this, {0, 0, 0});
	fSys->addForceGenerator(vgen);
	vgen->setRadius(100);
}
