#include "ParticleScene.h"
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


	// ----- PARTICULA -----
	//addParticle( new Particle({0,0,0}, {0,1,0}, {0,10,0}, 0.98));
	// ----- PROYECTIL -----
	//scene->addGameObject(new Proyectile({ 0,0,0 }, { 25,25,0 }));


	// ------- SISTEMAS DE PARTICULAS ------
	ParticleSystem* partsyst = new ParticleSystem(this);
	addSystem(partsyst);


	//------ Sistema 4 ------
	// sistema de particula cascada
	partsyst->addParticleGenerator(new CascadaGen(Vector3(0, 50, 0), 10000, partsyst, this));

	//------ Sistema 2 ------
	// sistema de particula niebla
	//partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst));

	// ------ Sistema 3 -----
	// sistema de particula disparo
	//partsyst->addParticleGenerator(new Disparo(Vector3(0, 10, 0), 10, partsyst));
	// sistema de particula sangre
	//partsyst->addParticleGenerator(new Sangre(Vector3(0, 10, 50), 15, partsyst));
	
	//// --------- SISTEMA DE FUERZAS ------------
	//ForceSystem* fSys = new ForceSystem(this);
	//addSystem(fSys);

	//// generador de viento
	//VientoGenerador* vgen = new VientoGenerador({ 0,0,0 }, this, { 5,0,0 });
	//fSys->addForceGenerator(vgen);

	//vgen->setRadious(20);
}
