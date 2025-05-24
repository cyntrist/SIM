#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"
#include "ForceGenerator.h"

class WhirlScene : public Scene
{
	ParticleSystem* partSyst = nullptr;
	ForceSystem* forceSyst = nullptr;

	ParticleGenerator* partGen = nullptr;
	WhirlwindGenerator* whirlGen = nullptr;

public:
	WhirlScene(Camera* cam = nullptr) : Scene(cam)
	{
	};
	void setup() override;
	void onEnable() override;
	void onDisable() override;
};
