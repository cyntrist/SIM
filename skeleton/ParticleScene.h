#pragma once
#include "Scene.h"

class ParticleSystem;
class ForceSystem;
class WindGenerator;

class ParticleScene : public Scene
{
	ParticleSystem* partSyst = nullptr;

public:
	ParticleScene(Camera* cam = nullptr);

	void setup() override;
	void onEnable() override;
	void onDisable() override;
};
