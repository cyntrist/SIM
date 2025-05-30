#include "RigidBodyScene.h"
#include "RigidBody.h"

void RigidBodyScene::onEnable()
{
	Scene::onEnable();

	StaticRigidBody* suelo = new StaticRigidBody(this, gPhysics, gScene);
	suelo->setShape(CreateShape(PxBoxGeometry(100, 100, 100)), 100);
	suelo->setPosition({ 0,-100,0 });
	addGameObject(suelo);

	//RBDynamic* box1 = new RBDynamic("caja", this, gPhysics, gScene);
	//caja->setPosition({ 0,0,0 });
	//caja->setDensity(1);
	//addGameObject(caja);

	//RBDynamic* box2 = new RBDynamic("caja2", this, gPhysics, gScene);
	//caja2->setPosition({ 0,20,0 });
	//caja2->setDensity(100);
	//addGameObject(caja2);


}

void RigidBodyScene::onDisable()
{
	Scene::onDisable();
}
