#include "Widget.h"

#include <iostream>


Widget::Widget(string nam, Scene* scn, Vector3 Pos, float siz) : GameObject(nam, scn)
{
	pose = new PxTransform(Pos);
	size = siz;

	if (siz > 0)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(siz)), pose, {1, 0.0, 0.0, 0.01});
}

Widget::Widget(string nam, Scene* scn, Vector3 Pos, PxShape* shap) : GameObject(nam, scn)
{
	pose = new PxTransform(Pos);

	if (shap != nullptr)
		renderItem = new RenderItem(shap, pose, {1, 0.0, 0.0, 0.01});
	else
		cout << "ERROR AL CREAR WIDGET" << endl;
}

void Widget::changeShape(PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, pose, {1, 0.0, 0.0, 0.01});
	else
		renderItem->shape = shap;
}
