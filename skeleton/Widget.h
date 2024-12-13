#pragma once
#include "GameObject.h"

class Widget : public GameObject
{
public:
	Widget(string nam, Scene* scn, Vector3 Pos = {0, 0, 0}, float siz = 1);
	Widget(string nam, Scene* scn, Vector3 Pos = {0, 0, 0}, PxShape* shap = nullptr);

	~Widget() override
	{
	};

	void changeShape(PxShape* shap);

	bool update(double t) override { return true; }
};
