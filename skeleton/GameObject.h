#pragma once
#include "RenderUtils.hpp"
#include <string>
#include <PxPhysicsAPI.h>
#include "Global.h"

class Scene;

// Clase abstracta para todos los objetos que tengan update y puedan morir
class GameObject
{
protected:
	Scene* scene = nullptr;
	string name;
	bool alive = true;
	bool visible = true;

	RenderItem* renderItem = nullptr;
	PxShape* shape = nullptr;
	PxTransform* pose = nullptr;
	Vector4 color;
	float size = 3;
	float mass = 1;
	Vector3 vel = {0, 0, 0};

public:
	GameObject(string nam, Scene* scn) : scene(scn), name(nam)
	{
	}

	virtual ~GameObject() { DeregisterRenderItem(renderItem); }

	virtual bool update(double t);

	void setName(string name) { this->name = name; }
	string getName() const { return name; }
	bool isAlive() const { return alive; }
	bool isVisible() const { return visible; }

	virtual void setVisible(bool vis)
	{
		visible = vis;
		visible ? RegisterRenderItem(renderItem) : DeregisterRenderItem(renderItem);
	}

	void toggleVisible() { visible = !visible; }
	void kill() { alive = false; }

	virtual Vector3 getPosition() { return pose->p; }
	virtual PxQuat getRotation() { return pose->q; }
	float getSize() const { return size; }
	float getMass() const { return mass; }
	Vector3 getVel() { return vel; }
	string& getName() { return name; }

	virtual void setPosition(const Vector3 pos) { pose->p = pos; }
	virtual void setRotation(const PxQuat rot) { pose->q = rot; }
	void setSize(float siz) { size = siz; }
	void setMass(float mas) { mass = mas; }
	void setVel(const Vector3& vel) { this->vel = vel; }

	virtual void setShape(PxShape* shp, float siz)
	{
		renderItem->shape = shp;
		shape = shp;
		size = siz;
	}

	virtual void setColor(Vector4 col)
	{
		renderItem->color = col;
		color = col;
	}

	virtual void addForce(float x, float y, float z)
	{
	}

	virtual void addForce(Vector3 fc)
	{
	}
};
