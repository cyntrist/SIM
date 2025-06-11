#pragma once

#include "Scene.h"
class Griddle;
class SceneManager;
class Receiver;
class ForceSystem;
class RigidBodySystem;
class StaticRigidBody;
class DynamicRigidBody;

constexpr float ROT = 1.5708;

class Level : public Scene
{
protected:
	SceneManager* sm = nullptr;
	RigidBodySystem* rbSys = nullptr;
	ForceSystem* fSys = nullptr;
	std::vector<DynamicRigidBody*> griddles; // vector of dynamic rigid bodies
	int cDrb = 0; // current dynamic rigid body
	double stepAngle = 0.05;
	PxVec4 nColor = { 0.1, 0.4f, 0.2f, 1 },
		sColor = { 0.2, 0.8, 0.5, 1 };
	RenderItem* water = nullptr;
	Receiver* receiver = nullptr;
	double counter = 0, timer = 1000;
	bool won = false;
	int nextLevel = 0;
public:
	Level(PxPhysics* gphys, PxScene* gscn, SceneManager* sm = nullptr, Camera* cam = nullptr)
		: Scene(cam, gphys, gscn), sm(sm)
	{

	}

	void update(double t) override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
	void specialKeyPressed(int key, const PxTransform& camera) override;
	virtual void setGriddles() {}
	virtual void setSystems(){}
	virtual void setReceiver() {}
	virtual void setWater();
	virtual Griddle* addGriddle(PxVec3 pos, PxMaterial* mat = nullptr, PxVec3 vol = { 20, 0.5, 10 });
};


class Level1 : public Level
{
public:
	Level1(PxPhysics* gphys, PxScene* gscn, SceneManager* sm = nullptr, Camera* cam = nullptr)
	: Level(gphys, gscn, sm, cam)
	{
		lowerThreshold = 150;
		upperThreshold = 100;
		nextLevel = 2;
	}
	~Level1() override;

	void onEnable() override;
	void onDisable() override;
	void setGriddles() override;
	void setSystems() override;
	void setReceiver() override;
};

class Level2 : public Level
{

public:
	Level2(PxPhysics* gphys, PxScene* gscn, SceneManager* sm = nullptr, Camera* cam = nullptr)
		: Level(gphys, gscn, sm)
	{
		lowerThreshold = 150;
		upperThreshold = 100;
		nextLevel = 3;
	}
	~Level2() override;

	void onEnable() override;
	void onDisable() override;
	void setGriddles() override;
	void setSystems() override;
	void setReceiver() override;
};

class Level3 : public Level
{

public:
	Level3(PxPhysics* gphys, PxScene* gscn, SceneManager* sm = nullptr, Camera* cam = nullptr)
		: Level(gphys, gscn, sm)
	{
		lowerThreshold = 150;
		upperThreshold = 100;
		nextLevel = 0;
	}
	~Level3() override;

	void onEnable() override;
	void onDisable() override;
	void setGriddles() override;
	void setSystems() override;
	void setReceiver() override;
};
