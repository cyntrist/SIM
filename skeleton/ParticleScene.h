#pragma once
#include "Scene.h"

class ParticleScene : public Scene
{
public:
	ParticleScene(Camera* cam = nullptr);

	void setup() override;
};
