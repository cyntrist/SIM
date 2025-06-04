#include "TestScene.h"
#include "RigidBody.h"

TestScene::~TestScene()
{
}

void TestScene::onEnable()
{
	Scene::onEnable();

	drb = new DynamicRigidBody(this, gPhysics, gScene);
	drb->setPosition({ 5,20,0 });
	drb->setDensity(1);
	drb->setKinematic(true); 
	addGameObject(drb);
}

void TestScene::onDisable()
{
	Scene::onDisable();
}

void TestScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);

	auto k = std::tolower(key);

	switch (k)
	{
	case 'q':
		if (drb != nullptr) drb->setRotation(stepAngle);
		break;
	case 'e':
		if (drb != nullptr) drb->setRotation(-stepAngle);
		break;
	default:
		break;
	}
}
