#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"
#include "ForceGenerator.h"

class WindScene : public Scene
{
public:
	WindScene(Camera* cam = nullptr) : Scene(cam)
	{
	};
	void setup() override;
};
