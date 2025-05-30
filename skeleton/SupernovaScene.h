#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"

class SupernovaScene : public Scene
{
	ExplosionGenerator* explosionGen = nullptr;
	ParticleSystem* partSyst = nullptr;
	ForceSystem* forceSyst = nullptr;

public:
	SupernovaScene(Camera* cam = nullptr) : Scene(cam) {};

	void setup() override;
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
};