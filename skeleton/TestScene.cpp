#include "TestScene.h"
#include "RigidBody.h"

TestScene::~TestScene()
{
}

void TestScene::onEnable()
{
	Scene::onEnable();


	srb = new StaticRigidBody(this, gPhysics, gScene);
	srb->setShape(CreateShape(PxBoxGeometry(10, 2, 10)), 10);
	srb->setPosition({ 0,50,0 });
	srb->setRotation(PxQuat(99));
	addGameObject(srb);


	//DynamicRigidBody* box1 = new DynamicRigidBody(this, gPhysics, gScene);
	//box1->setPosition({ 5,20,0 });
	//box1->setDensity(1);
	//addGameObject(box1);
}

void TestScene::onDisable()
{
	Scene::onDisable();
}

void TestScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);

	switch (key)
	{
	case 'q':
		if (srb != nullptr) srb->setRotation(PxQuat(0.5));
		break;
	case 'e':
		if (srb != nullptr) srb->setRotation(PxQuat(-0.5));
		break;
	default:
		break;
	}
}
