#include "TestScene.h"
#include "RigidBody.h"

TestScene::~TestScene()
{
}

void TestScene::onEnable()
{
	Scene::onEnable();

	//srb = new StaticRigidBody(this, gPhysics, gScene);
	//srb->setShape(CreateShape(PxBoxGeometry(10, 2, 10)), 10);
	//srb->setPosition({ 0,50,0 });
	//srb->setRotation(PxQuat(0.5));
	//addGameObject(srb);

	drb = new DynamicRigidBody(this, gPhysics, gScene);
	drb->setPosition({ 5,20,0 });
	drb->setDensity(1);
	drb->setKinematic(true);
	drb->setRotation(10);
	addGameObject(drb);
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
		if (drb != nullptr) drb->setRotation(0.05);
		break;
	case 'e':
		if (drb != nullptr) drb->setRotation(-0.05);
		break;
	default:
		break;
	}
}
