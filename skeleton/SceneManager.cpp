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
	//...
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
		scene->hide();
	actualScene = id;
	scenes[id]->show();
	Log("SCENE " + to_string(id));
}

void SceneManager::keyPressed(unsigned char key, const PxTransform& camera)
{
	int index = -1;
	switch (toupper(key))
	{
	case '0':
		index = 0;
		break;
	case'1':
		index = 1;
		break;
	case'2':
		index = 2;
		break;
	case'3':
		index = 3;
		break;
	case'4':
		index = 4;
		break;
	default:
		for (const auto& s : scenes)
			s->keyPressed(key, camera);
		break;
	}

	if (index != -1)
		setScene(toupper(key));
}
