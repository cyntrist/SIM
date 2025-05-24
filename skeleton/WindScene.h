#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"
#include "ForceGenerator.h"

class WindScene : public Scene
{
	ParticleSystem* partSyst = nullptr;
	ForceSystem* forceSyst = nullptr;
	WindGenerator* windGen = nullptr;

public:
	WindScene(Camera* cam = nullptr) : Scene(cam)
	{
	};
	void setup() override;
	void onEnable() override;
	void onDisable() override;
};
