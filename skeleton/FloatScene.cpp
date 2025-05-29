#include "FloatScene.h"

#include "ForceSystem.h"

void FloatScene::setup()
{

}

void FloatScene::onEnable()
{
	Scene::onEnable();

	float height = 45;
	float offset = 5;

	auto fsys = new ForceSystem(this);
	addSystem(fsys);

	/// FLOTACION
	fsys->addForceGenerator(new FlotationGenerator(this, height, 10000));

	// particula encima del agua
	auto partFlot = new Particle(this, { -10, height + offset, 0 });
	addGameObject(partFlot);
	partFlot->toggleGrav();
	partFlot->setSize(1);
	partFlot->setMass(100);
	partFlot->setColor({ 0.4, 0.5, 0.3, 1 });

	// particula suspendida en el liquido
	auto partIntermedio = new Particle(this, { 0, height + offset, 0 });
	addGameObject(partIntermedio);
	partIntermedio->toggleGrav();
	partIntermedio->setSize(0.5);
	partIntermedio->setMass(1000);
	partIntermedio->setColor({ 0.75, 0.2, 0.5, 1 });

	// particula hundiendose
	auto partHundida = new Particle(this, { 10, height + offset, 0 });
	addGameObject(partHundida);
	partHundida->toggleGrav();
	partHundida->setSize(0.5);
	partHundida->setMass(10000);
	partHundida->setColor({ 0.1, 0.5, 0.5, 1 });



	// superficie del liquido
	auto superficieLiquido = new Particle(this, { 0, height, 0 });
	addGameObject(superficieLiquido);
	superficieLiquido->setImmovible(true);
	superficieLiquido->setColor(0.1, 0.2, 0.4, 1.0);
	superficieLiquido->setShape(CreateShape(PxBoxGeometry(20, 0.2, 20)), 20);

	// suelo flotacion
	auto sueloF = new Particle(this, { 0, 0, 0 });
	addGameObject(sueloF);
	sueloF->setImmovible(true);
	sueloF->setColor({ .3, .2, .1, 0 });
	sueloF->setShape(CreateShape(PxBoxGeometry(20, 0.2, 20)), 20);
}

void FloatScene::onDisable()
{
	Scene::onDisable();
}
