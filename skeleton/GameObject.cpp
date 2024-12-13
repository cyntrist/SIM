#include "GameObject.h"
#include "Scene.h"

bool GameObject::update(double t)
{
	if (!alive)
		scene->deleteObject(name);
	return alive;
}
