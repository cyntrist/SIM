#pragma once
#include "Scene.h"

class SceneManager;
class ParticleSystem;
class FireworkSystem;

class FireworkScene : public Scene
{
	SceneManager* sm = nullptr;
	ParticleSystem* partSyst = nullptr;
	FireworkSystem* firewSyst1 = nullptr;
	FireworkSystem* firewSyst2 = nullptr;
public:
	FireworkScene(SceneManager* sm, Camera* c = nullptr) : Scene(c), sm(sm)
	{
		
	}
	void onEnable() override;
	void onDisable() override;
};
