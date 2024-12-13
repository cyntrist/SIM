#pragma once
#include "ForceGenerator.h"
#include "Scene.h"

class FloatScene : public Scene
{
public:
	FloatScene(Camera* cam = nullptr) : Scene(cam)
	{
	};

	void setup() override;

};
