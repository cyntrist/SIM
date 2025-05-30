#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"

class ExplosionScene : public Scene
{
	ExplosionGenerator* explosionGen = nullptr;
	ParticleSystem* partSyst;
	ForceSystem* forceSyst;

public:
	ExplosionScene(Camera* cam) : Scene(cam) {};

	void setup() override;
	void onEnable() override;
	void onDisable() override;
	void keyPressed(unsigned char key, const PxTransform& camera) override;
};