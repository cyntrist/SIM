#pragma once
#include "Scene.h"

class RigidBodyScene : public Scene
{

public:
	RigidBodyScene(Camera* cam = nullptr) : Scene(cam)
	{
	};
	void setup() override {};
	void onEnable() override;
	void onDisable() override;
};
