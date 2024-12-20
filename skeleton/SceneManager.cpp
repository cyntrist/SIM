﻿#include "SceneManager.h"
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
	if (actualScene < scenes.capacity())
		scenes[actualScene]->update(t);
}

void SceneManager::setScene(int id)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (i == id)
			scenes[i]->show();
		else
			scenes[i]->hide();
	}
	actualScene = id;
}

void SceneManager::keyPressed(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
	case '0':
		setScene(0);
		cout << "-- ESCENA 0 --" << endl;
		break;
	case'1':
		cout << "-- ESCENA 1 --" << endl;
		setScene(1);
		break;
	case'2':
		cout << "-- ESCENA 2 --" << endl;
		setScene(2);
		break;
	case'3':
		cout << "-- ESCENA 3 --" << endl;
		setScene(3);
		break;
	case'4':
		cout << "-- ESCENA 4 --" << endl;
		setScene(4);
		break;

	default:
		for (auto s : scenes)
			s->keyPressed(key, camera);

		break;
	}
}
