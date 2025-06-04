#include "Level.h"
#include "RigidBody.h"

Level::~Level()
{
	for (const auto& b : drbs)
		delete b;
}

void Level::onEnable()
{
	Scene::onEnable();

	auto drb = new DynamicRigidBody(this, gPhysics, gScene);
	drb->setPosition({ 5,20,0 });
	drb->setDensity(1);
	drb->setKinematic(true);
	drbs.push_back(drb);
	addGameObject(drb);
}

void Level::onDisable()
{
	Scene::onDisable();
}

void Level::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);

	auto k = std::tolower(key);

	switch (k)
	{
	case 'q':
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(stepAngle);
		break;
	case 'e':
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(-stepAngle);
		break;
	default:
		break;
	}
}

void Level::specialKeyPressed(int key, const PxTransform& camera)
{
	Scene::specialKeyPressed(key, camera);


	switch (key)
	{
	case GLUT_KEY_UP:
		Log("UP");
		break;
	case GLUT_KEY_DOWN:
		Log("DOWN");
		break;
	case GLUT_KEY_LEFT:
		Log("LEFT");
		break;
	case GLUT_KEY_RIGHT:
		Log("RIGHT");
		break;
	}
}
