﻿#include "WindScene.h"

void WindScene::setup()
{
	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);

	// denerador de particula niebla
	partsyst->addParticleGenerator(new RandomParticleGen(Vector3(0, 0, 0), 1000, partsyst, this));


	// --------- SISTEMA DE FUERZAS ------------
	ForceSystem* fSys = new ForceSystem(this);
	addSystem(fSys);

	// generador de viento
	VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, this, { 0,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadius(100);
}
