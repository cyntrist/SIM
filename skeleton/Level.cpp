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

	auto drb1 = new DynamicRigidBody(this, gPhysics, gScene);
	drb1->setPosition({ -25,10,50 });
	drb1->setKinematic(true);
	drb1->setColor(Vector4(0.5,0.5,0.5,1));
	drbs.push_back(drb1);
	addGameObject(drb1);

	auto drb2 = new DynamicRigidBody(this, gPhysics, gScene);
	drb2->setPosition({ 0,10,50 });
	drb2->setKinematic(true);
	drb2->setColor(Vector4(0.5, 0.5, 0.5, 1));
	drbs.push_back(drb2);
	addGameObject(drb2);

	auto drb3 = new DynamicRigidBody(this, gPhysics, gScene);
	drb3->setPosition({ 25,10,50 });
	drb3->setKinematic(true);
	drb3->setColor(Vector4(0.5, 0.5, 0.5, 1));
	drbs.push_back(drb3);
	addGameObject(drb3);
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
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(-stepAngle);
		break;
	case 'e':
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(stepAngle);
		break;
	default:
		break;
	}
}

void Level::specialKeyPressed(int key, const PxTransform& camera)
{
	Scene::specialKeyPressed(key, camera);

	int modifiers = glutGetModifiers();

	auto angle = stepAngle;
	auto times = 5;

	if (modifiers & GLUT_ACTIVE_SHIFT)
		angle /= times;
	else if (modifiers & GLUT_ACTIVE_CTRL)
		angle *= times;

	switch (key)
	{
	case GLUT_KEY_UP:
		cDrb++;
		break;
	case GLUT_KEY_DOWN:
		cDrb--;
		break;
	case GLUT_KEY_LEFT:
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(-angle);
		break;
	case GLUT_KEY_RIGHT:
		if (drbs[cDrb] != nullptr) drbs[cDrb]->setRotation(angle);
		break;
	}

	cDrb = min(max(cDrb, 0), drbs.size()-1);
}
