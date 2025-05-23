#include "ParticleScene.h"

#include "ForceSystem.h"
#include "ParticleSystem.h"

ParticleScene::ParticleScene(Camera* cam) : Scene(cam)
{
}

void ParticleScene::setup()
{
	//auto system = new ParticleSystem(this);
	//auto p1 = new ParticleGenerator(Vector3(0, 0, 0), Vector3(0, 10, 0), 1000);
	//auto p2 = new ParticleGenerator(Vector3(100, 0, 0), Vector3(0, 20, 0), 1000);
	//auto p3 = new ParticleGenerator(Vector3(50, 0, -100), Vector3(0, 30, 0), 1000);
	//p2->setMode(Mode::FUEGOS);
	//p3->setMode(Mode::HUMO);
	//system->addParticleGenerator(p1);
	//system->addParticleGenerator(p2);
	//system->addParticleGenerator(p3);
	////system->addParticleGenerator(new ParticleGenerator());
	////system->addParticleGenerator(new ParticleGenerator());

	auto partsyst = new ParticleSystem(this);
	addSystem(partsyst);
	partsyst->addParticleGenerator(new CascadaGen(Vector3(0, 50, 0), 100, partsyst, this));

	auto fSys = new ForceSystem(this);
	addSystem(fSys);
	auto vgen = new VientoGenerador({ 0,0,0 }, this, { 5,0,0 });
	fSys->addForceGenerator(vgen);

	vgen->setRadius(20);
}
