#include "WhirlScene.h"

void WhirlScene::setup()
{
	// ------- SISTEMAS DE PARTICULAS ------
	auto partsyst = new ParticleSystem(this);
	addSystem(partsyst);

	// sistema de particula niebla
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));

	// --------- SISTEMA DE FUERZAS ------------
	auto fSys = new ForceSystem(this);
	addSystem(fSys);

	// generador de torvellino
	auto tgen = new TorbellinoGenerator({0, 0, 0}, this);
	fSys->addForceGenerator(tgen);

	tgen->setRadius(100);
}
