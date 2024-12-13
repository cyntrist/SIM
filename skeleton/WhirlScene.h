#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"
#include "ForceGenerator.h"

class WhirlScene : public Scene
{
public:
	WhirlScene(Camera* cam) : Scene(cam)  {};
	~WhirlScene() {};

	void setup() override;
};
