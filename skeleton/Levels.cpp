#include "Levels.h"

#include "ForceSystem.h"
#include "ForceGenerator.h"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodySystem.h"
#include "SceneManager.h"

void Level::update(double t)
{
	Scene::update(t);
	if (receiver == nullptr) return;

	if (receiver->getWon())
	{
		receiver->setWon(false);
		won = true;
		if (sm != nullptr)
			sm->setLevelWon(true);
	}

	if (won)
	{
		counter += 1;
		if (counter >= timer)
		{
			counter = 0;
			if (sm != nullptr)
				sm->setScene(nextLevel);
			//Log("!!!WON!!!");
		}
	}
}

void Level::keyPressed(unsigned char key, const PxTransform& camera)
{
	Scene::keyPressed(key, camera);
	if (key == ' ' && rbSys != nullptr)
		rbSys->setActive(!rbSys->getActive());
}

void Level::specialKeyPressed(int key, const PxTransform& camera)
{
	Scene::specialKeyPressed(key, camera);
	if (griddles.empty()) return;

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

void Level::setWater()
{
	// Flotacion
	float height = -15;
	float k = 1.0f;
	fSys->addForceGenerator(new FlotationGenerator(this, height, k));
	// Agua
	water = new RenderItem(CreateShape(
		PxBoxGeometry(1000, 0.01, 100)),
		new PxTransform(PxVec3(0, height, 50)),
		{ 0.01f, 0.02f, 0.89f, 0.5f }
	);
}



/// LEVEL 1
#pragma region Level 1
Griddle* Level::addGriddle(PxVec3 pos, PxMaterial* mat, PxVec3 vol)
{
	auto drb = new Griddle(
		this, gPhysics, gScene, mat, true, vol, pos
	);
	drb->setRotation(ROT);
	griddles.push_back(drb);
	addGameObject(drb);
	drb->setColor(nColor);
	return drb;
}

Level1::~Level1()
{
	for (const auto& b : griddles)
		delete b;
}

void Level1::onEnable()
{
	Scene::onEnable();
	setGriddles();
	setSystems();
	setReceiver();
}

void Level1::onDisable()
{
	active = false;
	if (water != nullptr) water->release();
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
	systems.clear();
	gameObjects.clear();
	griddles.clear();
}

void Level1::setGriddles()
{
	PxVec3 volumen = {20, 0.5, 10};
	float y = 15, z = 50;

	PxMaterial* material = gPhysics->createMaterial(
		0.0001f, // friccion estatica
		0.0001f, // friccion dinamica
		1.75f // restitucion
	);

	addGriddle({ 0, y, z }, material);

	griddles[cDrb]->setColor(sColor);
}

void Level1::setSystems()
{
	PxVec3 pos = {60, 30, 50}, vel = {-13, 20, 0};
	/// RIGID BODY SYSTEM
	rbSys = new RigidBodySystem(this, gPhysics, gScene);
	addSystem(rbSys);

	auto rbg = new RigidBodyGenerator(
		pos,
		100,
		gPhysics,
		gScene,
		rbSys,
		vel
	);
	rbSys->addRBGenerator(rbg);
	rbg->setDummy();


	/// FORCE SYSTEMS
	fSys = new ForceSystem(this);
	addSystem(fSys);
	// Viento
	//auto windGen = new WindGenerator({ -10,25,50 }, this, { -20,0,0 });
	//fSys->addForceGenerator(windGen);
	//windGen->setRadius(15);

	setWater();
}

void Level1::setReceiver()
{
	PxVec3 vol = {3, 3, 3},
	       pos = {-50, 30, 50};

	// Ancla Superior
	auto anch1 = new Particle(this, {pos.x, pos.y + 20, pos.z});
	addGameObject(anch1);
	anch1->setImmovible(true);
	anch1->setColor({0.3, 0.3, 0.3, 1.0});
	anch1->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Ancla inferior
	//auto anch2 = new Particle(this, { pos.x, pos.y - 20, pos.z });
	//addGameObject(anch2);
	//anch2->setImmovible(true);
	//anch2->setColor({ 0.3, 0.3, 0.3, 1.0 });
	//anch2->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Recibidor
	receiver = new Receiver(this, gPhysics, gScene, false, vol, pos, 1, 1, -1);
	//receiver->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	addGameObject(receiver);
	receiver->setRotation(ROT);
	receiver->setMass(2);
	receiver->setLockFlags();

	// Gomas
	fSys->addForceGenerator(new RubberGenerator(
			this, 2, 10,
			receiver, anch1)
	);
	//fSys->addForceGenerator(new RubberGenerator(
	//	this, 1000, 5,
	//	receiver, anch2)
	//);
}
#pragma endregion Level 1



/// LEVEL 2
#pragma region Level 2
Level2::~Level2()
{
	for (const auto& b : griddles)
		delete b;
}

void Level2::onEnable()
{
	Scene::onEnable();
	setGriddles();
	setSystems();
	setReceiver();
}

void Level2::onDisable()
{
	active = false;
	if (water != nullptr) water->release();
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
	systems.clear();
	gameObjects.clear();
	griddles.clear();
}

void Level2::setGriddles()
{
	float x1 = 50, x2 = 0, x3 = -50,
		y1 = -15, y2 = 50;

	PxMaterial* material = gPhysics->createMaterial(
		0.0001f, // friccion estatica
		0.0001f, // friccion dinamica
		1.75f // restitucion
	);

	addGriddle({x1, y2, z}, material);
	addGriddle({x2, y1, z}, material);
	addGriddle({x3, y2, z}, material);

	cDrb = 0;
	griddles[cDrb]->setColor(sColor);
}

void Level2::setSystems()
{
	PxVec3 pos = {100, 0, z}, vel = {-50, 50, 0};
	/// RIGID BODY SYSTEM
	rbSys = new RigidBodySystem(this, gPhysics, gScene);
	addSystem(rbSys);

	auto rbg = new RigidBodyGenerator(
		pos,
		100,
		gPhysics,
		gScene,
		rbSys,
		vel
	);
	rbSys->addRBGenerator(rbg);
	rbg->setDummy();

	/// FORCE SYSTEMS
	fSys = new ForceSystem(this);
	addSystem(fSys);
	setWater();
}

void Level2::setReceiver()
{
	PxVec3 vol = {3, 3, 3},
	       pos = {-90, 5, z};

	// Ancla Superior
	auto anch1 = new Particle(this, {pos.x - 20, pos.y + 20, pos.z});
	addGameObject(anch1);
	anch1->setImmovible(true);
	anch1->setColor({0.3, 0.3, 0.3, 1.0});
	anch1->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Ancla inferior
	auto anch2 = new Particle(this, { pos.x + 20, pos.y - 20, pos.z });
	addGameObject(anch2);
	anch2->setImmovible(true);
	anch2->setColor({ 0.3, 0.3, 0.3, 1.0 });
	anch2->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Recibidor
	receiver = new Receiver(this, gPhysics, gScene, false, vol, pos, 1, 1, -1);
	//receiver->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	addGameObject(receiver);
	receiver->setMass(10);
	receiver->setRotation(-ROT / 2);
	receiver->setLockFlags();
	receiver->setTied(true);

	// Gomas
	fSys->addForceGenerator(new RubberGenerator(
			this, 10, 3,
			receiver, anch1)
	);
	fSys->addForceGenerator(new RubberGenerator(
		this, 10, 3,
		receiver, anch2)
	);
}
#pragma endregion Level 2



/// LEVEL 3
#pragma region Level 3
Level3::~Level3()
{
	for (const auto& b : griddles)
		delete b;
}

void Level3::onEnable()
{
	Scene::onEnable();
	setGriddles();
	setSystems();
	setReceiver();
}

void Level3::onDisable()
{
	active = false;
	if (water != nullptr) water->release();
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
	systems.clear();
	gameObjects.clear();
	griddles.clear();
}

void Level3::setGriddles()
{
	float x1 = 50, x2 = 0, x3 = -50,
		y1 = -15, y2 = 50;

	PxMaterial* material = gPhysics->createMaterial(
		0.0001f, // friccion estatica
		0.0001f, // friccion dinamica
		1.75f // restitucion
	);

	addGriddle({ x1, y2, z }, material);
	addGriddle({ x2, y1, z }, material);
	addGriddle({ x3, y2, z }, material);

	cDrb = 0;
	griddles[cDrb]->setColor(sColor);
}

void Level3::setSystems()
{
	PxVec3 pos = { 100, 0, z }, vel = { -50, 50, 0 };
	/// RIGID BODY SYSTEM
	rbSys = new RigidBodySystem(this, gPhysics, gScene);
	addSystem(rbSys);

	auto rbg = new RigidBodyGenerator(
		pos,
		100,
		gPhysics,
		gScene,
		rbSys,
		vel
	);
	rbSys->addRBGenerator(rbg);
	rbg->setDummy();

	/// FORCE SYSTEMS
	fSys = new ForceSystem(this);
	addSystem(fSys);
	setWater();
}

void Level3::setReceiver()
{
	PxVec3 vol = { 3, 3, 3 },
		pos = { -90, 5, z };

	// Ancla Superior
	auto anch1 = new Particle(this, { pos.x - 20, pos.y + 20, pos.z });
	addGameObject(anch1);
	anch1->setImmovible(true);
	anch1->setColor({ 0.3, 0.3, 0.3, 1.0 });
	anch1->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Ancla inferior
	auto anch2 = new Particle(this, { pos.x + 20, pos.y - 20, pos.z });
	addGameObject(anch2);
	anch2->setImmovible(true);
	anch2->setColor({ 0.3, 0.3, 0.3, 1.0 });
	anch2->setShape(CreateShape(PxBoxGeometry(1, 1, 1)), 1);

	// Recibidor
	receiver = new Receiver(this, gPhysics, gScene, false, vol, pos, 1, 1, -1);
	//receiver->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	addGameObject(receiver);
	receiver->setMass(10);
	receiver->setRotation(-ROT / 2);
	receiver->setLockFlags();
	receiver->setTied(true);

	// Gomas
	fSys->addForceGenerator(new RubberGenerator(
		this, 10, 3,
		receiver, anch1)
	);
	fSys->addForceGenerator(new RubberGenerator(
		this, 10, 3,
		receiver, anch2)
	);
}
#pragma endregion Level 3