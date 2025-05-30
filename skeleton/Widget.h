#pragma once
#include "GameObject.h"

class Widget : public GameObject
{
public:
	Widget(Scene* scn, Vector3 pos = {0, 0, 0}, float siz = 1, Vector4 c = { 0, 0, 1, 0.01 });
	Widget(Scene* scn, Vector3 pos = {0, 0, 0}, PxShape* shap = nullptr, Vector4 c = { 0, 0, 1, 0.01 });

	void changeShape(PxShape* shap);
	bool update(double t) override { return true; }
};
