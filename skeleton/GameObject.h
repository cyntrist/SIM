#pragma once
#include "Global.h"

class Scene;

// Clase abstracta para todos los objetos que tengan update y puedan morir
class GameObject
{
	Scene* scene = nullptr;
	string name;
	bool alive = true;
	bool visible = true;

public:
	void setName(string name) { this->name = name; }
	string getName() const { return name; }
	bool isAlive() const { return alive; }
	bool isVisible() const { return visible; }
	void setVisible(bool vis) { visible = vis; }
	void toggleVisible() { visible = !visible; }
	void kill() { alive = false; }
	virtual bool update(double t) = 0;
};
