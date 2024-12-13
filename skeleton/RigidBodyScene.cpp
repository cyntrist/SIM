#include "RigidBodyScene.h"
#include "RigidBodyDynamic.h"
#include "RigidBodyStatic.h"

RigidBodyScene::RigidBodyScene(Camera* cam, PxPhysics* gPhycs, PxScene* gScn) : Scene(cam, gPhycs, gScn)
{
}

void RigidBodyScene::setup()
{
	auto suelo = new RBStatic("suelo", this, gPhysics);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 100, 100)), 200);
	suelo->setPosition({0, -200, 0});
	gScene->addActor(*suelo->getActor());
	addGameObject(suelo);


	auto caja = new RBDynamic("caja", this, gPhysics);
	caja->setPosition({0, 0, 0});
	caja->setDensity(100);
	gScene->addActor(*caja->getActor());
	addGameObject(caja);

	auto particle = new Particle("p3", this, {110, 20, 0});
	particle->setImmovible(false);
	particle->toggleGrav();
	particle->setFloor(-300);

	addGameObject(particle);
}
