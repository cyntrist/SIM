﻿#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"

class SpringScene : public Scene
{
private:
	ExplosionGenerator* expls = nullptr;
	SpringGenerator* sprngGen = nullptr;
public:
	SpringScene(Camera* cam) : Scene(cam) {};
	~SpringScene() {};

	void setup() override;

	void keyPressed(unsigned char key, const physx::PxTransform& camera);
};