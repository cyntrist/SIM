#include "SceneManager.h"
#include "FloatScene.h"
#include "RenderUtils.hpp"
#include "Scene.h"
#include "SpringScene.h"
#include "WhirlScene.h"
#include "WindScene.h"

SceneManager::SceneManager(PxPhysics* gphys, PxScene* gscn): gPhysics(gphys), gScene(gscn)
{
	addScene(new Scene()); // 0
	addScene(new ParticleScene()); // 1
	addScene(new WindScene()); // 2
	addScene(new WhirlScene()); // 3
	addScene(new SpringScene()); // 4
	addScene(new FloatScene()); // 5
	setScene(4);
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

void SceneManager::update(float t)
{
	scenes[actualScene]->update(t);
}

void SceneManager::setScene(int id)
{
	for (auto* scene : scenes)
		scene->show(false);

	scenes[id]->onDisable();
	actualScene = id;
	scenes[id]->onEnable();
	scenes[id]->show();

	Log("SETTING SCENE TO Nº " + to_string(id));
}

void SceneManager::keyPressed(unsigned char key, const PxTransform& camera)
{
	const int index = toupper(key) - 48;
	Log(to_string(key));

	for (const auto& s : scenes)
		s->keyPressed(key, camera);

	if (index > -1 && index < scenes.capacity())
		setScene(index);
}
