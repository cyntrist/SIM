#include "TestScene.h"
#include "RigidBody.h"

TestScene::~TestScene()
{
}

void TestScene::onEnable()
{
	Scene::onEnable();


	StaticRigidBody* suelo = new StaticRigidBody(this, gPhysics, gScene);
	suelo->setShape(CreateShape(PxBoxGeometry(10, 2, 10)), 10);
	suelo->setPosition({ 0,50,0 });
	addGameObject(suelo);


	//DynamicRigidBody* box1 = new DynamicRigidBody(this, gPhysics, gScene);
	//box1->setPosition({ 5,20,0 });
	//box1->setDensity(1);
	//addGameObject(box1);
}

void TestScene::onDisable()
{
	Scene::onDisable();
}
