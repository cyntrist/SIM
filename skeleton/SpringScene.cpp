#include "SpringScene.h"

void SpringScene::setup()
{
	// SYSTEMS
	auto fsys = new ForceSystem(this);
	addSystem(fsys);

	// --- MUELLES ---	
	// explosion para probar
	expls = new ExplosionGenerator({-20, 50, -10}, this);
	fsys->addForceGenerator(expls);
	expls->setRadius(30);
	expls->setPotencia(100);

	// suelo muelles
	auto sueloM = new Particle("sueloM", this, {-20, 20, 0});
	addGameObject(sueloM);
	sueloM->setImmovible(true);
	sueloM->setMaxLifetime(50);
	sueloM->setColor({.5, .5, .5, 0});
	sueloM->setShape(CreateShape(PxBoxGeometry(30, 0.2, 40)), 40);

	// particula a un ancla
	auto part1 = new Particle("part1", this, {-20, 70, 0});
	addGameObject(part1);
	part1->setMaxLifetime(50);
	part1->toggleGrav();
	part1->setColor({0.2, 0.2, 0.8, 1});
	part1->setFloor(20.5);

	// ancla
	auto anch = new Particle("anch", this, {-20, 70, 0});
	addGameObject(anch);
	anch->setImmovible(true);
	anch->setMaxLifetime(50);
	anch->setColor({0.2, 0.2, 0.8, 0});
	anch->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	fsys->addForceGenerator(new SpringGenerator(anch->getPosition(), this, 10, 7, part1));

	// cadena de particula
	auto part2 = new Particle("part2", this, {-20, 50, 2});
	addGameObject(part2);
	part2->setMaxLifetime(50);
	part2->toggleGrav();
	part2->setColor({0.2, 0.6, 0.8, 1});
	part2->setFloor(20.5);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part2, part1));

	// particula a otra particula
	auto part3 = new Particle("part3", this, {-20, 50, 0});
	addGameObject(part3);
	part3->setMaxLifetime(50);
	part3->toggleGrav();
	part3->setMass(2);
	part3->setColor({0.8, 0.6, 0.2, 1});
	part3->setFloor(20.5);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part3, part2));

	auto part4 = new Particle("part4", this, {-20, 50, -10});
	addGameObject(part4);
	part4->setMaxLifetime(50);
	part4->toggleGrav();
	part4->setColor({0.8, 0.2, 0.2, 1});
	part4->setFloor(20.5);
	part4->setMass(50);

	fsys->addForceGenerator(new GomaGenerator(this, 10, 7, part4, part3));


	// --- ANCLA K PERSONALIZABLE ---
	// ancla
	auto anch2 = new Particle("anch2", this, {-20, 70, -20});
	addGameObject(anch2);
	anch2->setImmovible(true);
	anch2->setMaxLifetime(50);
	anch2->setColor({0.2, 0.8, 0.2, 0});
	anch2->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);


	// cadena de particula
	auto partD = new Particle("partD", this, {-20, 70, -20});
	addGameObject(partD);
	partD->setMaxLifetime(50);
	partD->toggleGrav();
	partD->setColor({0.2, 0.8, 0.2, 1});
	partD->setFloor(20.5);

	sprngGen = new SpringGenerator(anch2->getPosition(), this, 10, 10, partD);
	fsys->addForceGenerator(sprngGen);


	// --- FLOTACION ---
	// generador de fuerza
	fsys->addForceGenerator(new FlotationGenerator(20, this, 1000));


	// particula encima del agua
	auto partFlot = new Particle("partFlot", this, {0, 30, -50});
	addGameObject(partFlot);
	partFlot->setMaxLifetime(50);
	partFlot->toggleGrav();
	partFlot->setSize(1);
	partFlot->setMass(100);
	partFlot->setColor({0.2, 0.8, 0.2, 1});

	// particula suspendida en el liquido
	auto partIntermedio = new Particle("partIntermedio", this, {10, 20, -50});
	addGameObject(partIntermedio);
	partIntermedio->setMaxLifetime(50);
	partIntermedio->toggleGrav();
	partIntermedio->setSize(0.5);
	partIntermedio->setMass(1000);
	partIntermedio->setColor({0.8, 0.8, 0.2, 1});

	// particula hundiendose
	auto partHundida = new Particle("partHundida", this, {20, 30, -50});
	addGameObject(partHundida);
	partHundida->setMaxLifetime(50);
	partHundida->toggleGrav();
	partHundida->setSize(1);
	partHundida->setMass(10000);
	partHundida->setColor({0.8, 0.2, 0.2, 1});

	// superficie del liquido
	auto superficieLiquido = new Particle("superficieLiquido", this, {10, 20, -50});
	addGameObject(superficieLiquido);
	superficieLiquido->setImmovible(true);
	superficieLiquido->setMaxLifetime(50);
	superficieLiquido->setColor({0.2, 0.2, 0.8, 0});
	superficieLiquido->setShape(CreateShape(PxBoxGeometry(20, 0.2, 10)), 20);

	// suelo flotacion
	auto sueloF = new Particle("SueloF", this, {10, 0, -50});
	addGameObject(sueloF);
	sueloF->setImmovible(true);
	sueloF->setMaxLifetime(50);
	sueloF->setColor({.5, .5, .5, 0});
	sueloF->setShape(CreateShape(PxBoxGeometry(20, 0.2, 10)), 20);
}

void SpringScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		expls->startGenerate();
		break;
	case 'z':
		sprngGen->setK(1);
		break;
	case 'x':
		sprngGen->setK(10);
		break;
	case 'c':
		sprngGen->setK(100);
		break;
	case 'v':
		sprngGen->setK(1000);
		break;
	default:
		break;
	}
}
