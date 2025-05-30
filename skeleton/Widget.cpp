#include "Widget.h"
#include <iostream>

Widget::Widget(Scene* scn, Vector3 pos, float siz, Vector4 c) : GameObject(scn)
{
	pose = new PxTransform(pos);
	size = siz;
	color = c;

	if (siz > 0) renderItem = new RenderItem(CreateShape(
		PxSphereGeometry(siz)), 
		pose, 
		color
	);
}

Widget::Widget(Scene* scn, Vector3 pos, PxShape* shap, Vector4 c) : GameObject(scn)
{
	pose = new PxTransform(pos);
	color = c;

	if (shap != nullptr)
		renderItem = new RenderItem(shap, pose, color);
	else
		Log("ERROR CREATING WIDGET");
}

void Widget::changeShape(PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, pose, color);
	else
		renderItem->shape = shap;
}
