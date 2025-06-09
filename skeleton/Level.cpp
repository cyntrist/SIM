#include "Level.h"

#include "ForceSystem.h"
#include "ForceGenerator.h"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodySystem.h"

Level::~Level()
{
	for (const auto& b : griddles)
		delete b;
}

void Level::onEnable()
{
	Scene::onEnable();
	setGriddles();
	setSystems();
}

void Level::onDisable()
{
	active = false;
	for (auto syst : systems)
	{
		delete syst;
		syst = nullptr;
	}
	for (auto obj : gameObjects)
	{
		delete obj;
		obj = nullptr;
	}
	//for (auto griddle : griddles)
	//{
	//	delete griddle;
	//	griddle = nullptr;
	//}
	systems.clear();
	gameObjects.clear();
	griddles.clear();
}

void Level::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);
	if (key == ' ')
		rbSys->setActive(!rbSys->getActive());
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
		if (griddles[cDrb] != nullptr) griddles[cDrb]->setRotation(-angle);
		break;
	case GLUT_KEY_RIGHT:
		if (griddles[cDrb] != nullptr) griddles[cDrb]->setRotation(angle);
		break;
	}

	int max = griddles.size() - 1ull;
	cDrb = PxClamp(cDrb, 0, max);
	for (auto& b : griddles)
		b->setColor(nColor);

	griddles[cDrb]->setColor(sColor);
}

void Level::setGriddles()
{
	PxVec3 volumen = {15, 2, 10};
	float x = 40, y = 10, z = 50;

	auto drb1 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {-x, y, z}
	);
	auto drb2 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {0, y, z}
	);
	auto drb3 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, {x, y, z}
	);

	griddles.push_back(drb1);
	griddles.push_back(drb2);
	griddles.push_back(drb3);

	addGameObject(drb1);
	addGameObject(drb2);
	addGameObject(drb3);

	griddles[cDrb]->setColor(sColor);
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

	fSys = new ForceSystem(this);
	addSystem(fSys);
	auto windGen = new WindGenerator({ 10,25,50 }, this, { 50,0,0 });
	fSys->addForceGenerator(windGen);
	windGen->setRadius(15);
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

void Level::update(double t)
{
	Scene::update(t);
}










Level2::~Level2()
{
}

void Level2::onEnable()
{
	Level::onEnable();
}

void Level2::onDisable()
{
	Level::onDisable();
}

void Level2::setGriddles()
{
	PxVec3 volumen = { 15, 2, 10 };
	float x = 40, y = 30, z = 50;

	auto drb1 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, { -x, y, z }
	);
	//auto drb2 = new DynamicRigidBody(
	//	this, gPhysics, gScene, true, BOX, volumen, { 0, y, z }
	//);
	auto drb3 = new DynamicRigidBody(
		this, gPhysics, gScene, true, BOX, volumen, { x, y, z }
	);

	griddles.push_back(drb1);
	//griddles.push_back(drb2);
	griddles.push_back(drb3);

	addGameObject(drb1);
	//addGameObject(drb2);
	addGameObject(drb3);

	griddles[cDrb]->setColor(sColor);
}

void Level2::setSystems()
{
	rbSys = new RigidBodySystem(this, gPhysics, gScene, this);
	addSystem(rbSys);

	auto rbg = new RigidBodyGenerator(
		{ 40, 45, 50 },
		50,
		gPhysics,
		gScene,
		rbSys,
		this
	);

	rbSys->addRBGenerator(rbg);
}

void Level2::update(double t)
{
	Level::update(t);
}

void Level2::specialKeyPressed(int key, const PxTransform& camera)
{
	Level::specialKeyPressed(key, camera);
}
