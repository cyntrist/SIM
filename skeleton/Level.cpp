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

	PxVec3 volumen = { 15, 2, 10 };

	auto drb1 = new DynamicRigidBody(this, gPhysics, gScene, volumen);
	drb1->setPosition({ -40,10,50 });
	drb1->setKinematic(true);
	drbs.push_back(drb1);
	addGameObject(drb1);

	auto drb2 = new DynamicRigidBody(this, gPhysics, gScene, volumen);
	drb2->setPosition({ 0,10,50 });
	drb2->setKinematic(true);
	drbs.push_back(drb2);
	addGameObject(drb2);

	auto drb3 = new DynamicRigidBody(this, gPhysics, gScene, volumen);
	drb3->setPosition({40,10,50 });
	drb3->setKinematic(true);
	drbs.push_back(drb3);
	addGameObject(drb3);

	drbs[cDrb]->setColor(sColor);
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

	cDrb = PxClamp(cDrb, size_t{}, drbs.size() - 1);
	for (auto& b : drbs)
		b->setColor(nColor);

	drbs[cDrb]->setColor(sColor);
}
