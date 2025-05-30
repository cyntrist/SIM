#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"

class SpringScene : public Scene
{
	ExplosionGenerator* expl1 = nullptr;
	ExplosionGenerator* expl2 = nullptr;
	SpringGenerator* sprngGen = nullptr;

public:
	SpringScene(Camera* cam = nullptr) : Scene(cam)
	{
	};

	void setup() override;
	void onEnable() override;
	void onDisable() override;

	void keyPressed(unsigned char key, const PxTransform& camera) override;
};
