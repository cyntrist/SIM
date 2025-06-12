#include "SceneManager.h"

#include "FireworkScene.h"
#include "SupernovaScene.h"
#include "FloatScene.h"
#include "RigidBodyScene.h"
#include "Scene.h"
#include "SpringScene.h"
#include "Levels.h"
#include "WhirlScene.h"
#include "WindScene.h"

SceneManager::SceneManager(PxPhysics* gphys, PxScene* gscn): gPhysics(gphys), gScene(gscn)
{
	//addScene(new Scene()); // 0
	//addScene(new ParticleScene()); // 1
	//addScene(new WindScene()); // 2
	//addScene(new WhirlScene()); // 3
	//addScene(new SpringScene()); // 4
	//addScene(new FloatScene()); // 5
	//addScene(new SupernovaScene()); // 6
	//addScene(new RigidBodyScene(gphys, gscn)); // 7

	addScene(new FireworkScene(this)); // 0
	addScene(new Level1(gphys, gscn, this)); // 1
	addScene(new Level2(gphys, gscn, this)); // 2
	addScene(new Level3(gphys, gscn, this)); // 3
	setScene(1);
}

SceneManager::~SceneManager()
{
	for (auto* scene : scenes)
		delete scene;
}

void SceneManager::addScene(Scene* scn)
{
	if (scn != nullptr)
	{
		scenes.push_back(scn);
		scn->setup();
	}
}

void SceneManager::update(double t)
{
	scenes[actualScene]->update(t);
}

void SceneManager::setScene(int id)
{
	//for (auto* scene : scenes)
	//	scene->show(false);

	scenes[actualScene]->onDisable();
	actualScene = id;
	scenes[id]->onEnable();
	scenes[id]->show();
	levelWon = false;

	Log("SETTING SCENE TO " + to_string(actualScene));
}

void SceneManager::keyPressed(unsigned char key, const PxTransform& camera)
{
	const int index = toupper(key) - 48;

	for (const auto& s : scenes)
		s->keyPressed(key, camera);

	if (index >= scenes.size())
		return;

	if (index > -1 && index != actualScene)
		setScene(index);
}

void SceneManager::specialKeyPressed(int key, const PxTransform& camera)
{
	for (const auto& s : scenes)
		s->specialKeyPressed(key, camera);
}
