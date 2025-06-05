#include "RigidBodyScene.h"
#include "RigidBody.h"

void RigidBodyScene::onEnable()
{
	Scene::onEnable();

	StaticRigidBody* suelo = new StaticRigidBody(this, gPhysics, gScene);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 100, 100)), 100);
	suelo->setPosition({ 0,-100,0 });
	addGameObject(suelo);

	DynamicRigidBody* box1 = new DynamicRigidBody(this, gPhysics, gScene);
	box1->setPosition({ 5,20,0 });
	box1->setDensity(1);
	addGameObject(box1);

	DynamicRigidBody* box2 = new DynamicRigidBody(this, gPhysics, gScene);
	box2->setPosition({ -5,50,0 });
	box2->setDensity(100);
	addGameObject(box2);
}

void RigidBodyScene::onDisable()
{
	Scene::onDisable();
}
