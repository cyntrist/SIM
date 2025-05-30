#include "Widget.h"
#include <iostream>

Widget::Widget(Scene* scn, Vector3 pos, float siz) : GameObject(scn)
{
	pose = new PxTransform(pos);
	size = siz;

	if (siz > 0) renderItem = new RenderItem(CreateShape(
		PxSphereGeometry(siz)), 
		pose, 
		{0, 0, 1, 0.01}
	);
}

Widget::Widget(Scene* scn, Vector3 pos, PxShape* shap) : GameObject(scn)
{
	pose = new PxTransform(pos);

	if (shap != nullptr)
		renderItem = new RenderItem(shap, pose, { 0, 0.0, 1.0, 0.01 });
	else
		Log("ERROR CREATING WIDGET");
}

void Widget::changeShape(PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, pose, {1, 0.0, 0.0, 0.01});
	else
		renderItem->shape = shap;
}
