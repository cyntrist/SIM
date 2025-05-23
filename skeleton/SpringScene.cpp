﻿#include "SpringScene.h"

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
	expls->setPower(100);


	///
	/// MUELLES
	///

	// ancla
	auto anch = new Particle("anch", this, {-20, 75, 0});
	addGameObject(anch);
	anch->setImmovible(true);
	anch->setColor({0.01, 0.2, 0.02, 0});
	anch->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// particula a un ancla
	auto part1 = new Particle("part1", this, {-20, 75, 0});
	addGameObject(part1);
	part1->toggleGrav();
	part1->setColor({0.01, 0.2, 0.01, 1});
	//part1->setFloor(20.5);

	fsys->addForceGenerator(new SpringGenerator(anch->getPosition(), this, 10, 7, part1));

	// cadena de particula
	auto part2 = new Particle("part2", this, {-20, 60, 0});
	addGameObject(part2);
	part2->toggleGrav();
	part2->setColor({0.05, 0.25, 0.1, 1});
	//part2->setFloor(20.5);

	fsys->addForceGenerator(new RubberGenerator(this, 10, 7, part2, part1));

	// particula a otra particula
	auto part3 = new Particle("part3", this, {-20, 50, 0});
	addGameObject(part3);
	part3->toggleGrav();
	part3->setMass(2);
	part3->setColor({0.1, 0.3, 0.1, 1});
	//part3->setFloor(20.5);

	fsys->addForceGenerator(new RubberGenerator(this, 10, 7, part3, part2));

	auto part4 = new Particle("part4", this, {-20, 40, 0});
	addGameObject(part4);
	part4->toggleGrav();
	part4->setColor({0.15, 0.4, 0.1, 1});
	//part4->setFloor(20.5);
	part4->setMass(5);

	fsys->addForceGenerator(new RubberGenerator(this, 10, 7, part4, part3));


	// --- ANCLA K PERSONALIZABLE ---
	// ancla
	Vector3 pos4(0, 75, -20);
	Vector4 color4(0.2, 0.05, 0.01, 1);
	auto anch2 = new Particle("anch2", this, pos4);
	addGameObject(anch2);
	anch2->setImmovible(true);
	anch2->setColor(color4);
	anch2->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);


	// particula a ancla
	auto partD = new Particle("partD", this, pos4);
	addGameObject(partD);
	partD->toggleGrav();
	partD->setColor(color4);
	//partD->setMass(10);
	//partD->setFloor(20.5);

	sprngGen = new SpringGenerator(anch2->getPosition(), this, 10, 10, partD);
	fsys->addForceGenerator(sprngGen);


	auto sueloM = new Particle("sueloM", this, {-00, -20, 0});
	addGameObject(sueloM);
	sueloM->setImmovible(true);
	sueloM->setColor({.01, .01, .05, 0});
	sueloM->setShape(CreateShape(PxBoxGeometry(50, 0.2, 50)), 40);
}

void SpringScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case 'e':
		if (expls != nullptr) expls->startGenerate();
		break;
	case 'z':
		sprngGen->setK(1);
		break;
	case 'x':
		sprngGen->setK(10);
		break;
	case 'c':
		sprngGen->setK(50);
		break;
	case 'v':
		sprngGen->setK(100);
		break;
	default:
		break;
	}
}
