#pragma once

// Clase abstracta para todos los objetos que tengan update y puedan morir
class SceneObject
{
	bool alive = true;

public:
	SceneObject();
	virtual ~SceneObject();

	bool isAlive() const { return alive; }
	void kill() { alive = false; }

	virtual bool update(double t) = 0;
};
