﻿#include "Level.h"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include  "RigidBodySystem.h"

Level::~Level()
{
	for (const auto& b : drbs)
		delete b;
}

void Level::onEnable()
{
	Scene::onEnable();
	setGriddles();
	setSystems();
	//generateBody();
}

void Level::onDisable()
{
	Scene::onDisable();
}

void Level::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);
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

	int max = drbs.size() - 1ull;
	cDrb = PxClamp(cDrb, 0, max);
	for (auto& b : drbs)
		b->setColor(nColor);

	drbs[cDrb]->setColor(sColor);
}

void Level::setGriddles()
{
	PxVec3 volumen = {15, 2, 10};
	float x = 40, y = 10, z = 50;

	auto drb1 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {-x, y, z}
	);
	drbs.push_back(drb1);
	addGameObject(drb1);

	auto drb2 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {0, y, z}
	);
	drbs.push_back(drb2);
	addGameObject(drb2);
	drb2->setVisible(false);
	auto drb3 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {x, y, z}
	);
	drbs.push_back(drb3);
	addGameObject(drb3);
	drbs[cDrb]->setColor(sColor);
}

void Level::setSystems()
{
	rbSys = new RigidBodySystem(this, gPhysics, gScene, this); 
	addSystem(rbSys);

	auto rbg = new RigidBodyGenerator(
		{40, 25, 50},
		50,
		gPhysics,
		gScene,
		rbSys,
		this
	);

	rbSys->addRBGenerator(rbg);
}

void Level::generateBody()
{
	PxVec3 volumen = { 1, 1, 1 };
	float x = 0, y = 0, z = 0;
	auto drb1 = new DynamicRigidBody(
		this, gPhysics, gScene, false, SPHERE, volumen, { -x,y,z }
	);
	drb1->setDensity(0.5f);
	drb1->setVisible(true);
	drb1->setMass(10);
	addGameObject(drb1);
}
