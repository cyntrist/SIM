#pragma once
#include "GameObject.h"

class Widget : public GameObject
{
public:
	Widget(Scene* scn, Vector3 pos = {0, 0, 0}, float siz = 1);
	Widget(Scene* scn, Vector3 pos = {0, 0, 0}, PxShape* shap = nullptr);

	~Widget() override = default;

	void changeShape(PxShape* shap);

	bool update(double t) override { return true; }
};
