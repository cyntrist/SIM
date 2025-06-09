#pragma once
#include "RenderUtils.hpp"
#include <string>
#include <PxPhysicsAPI.h>
#include "Global.h"

//using namespace physx;

class Scene;

// Clase abstracta para todos los objetos que tengan update y puedan morir
class GameObject
{
protected:
	Scene* scene = nullptr;
	bool alive = true;
	bool visible = true;
	int responsive = -1; // si va a tener callback en colision
	RenderItem* renderItem = nullptr;
	PxShape* shape = nullptr;
	PxTransform* pose = nullptr;
	Vector4 color;
	float size = 1;
	float mass = 1;
	Vector3 vel = {0, 0, 0};

public:
	GameObject(Scene* scn, float size = 3, float mass = 1) 
		: scene(scn), size(size), mass(mass) {}

	virtual ~GameObject()						{ DeregisterRenderItem(renderItem); }

	virtual bool update(double t)				{ return alive; }

	//void setName(const string& n)				{ name = n; }
	//string getName() const						{ return name; }
	bool isAlive() const						{ return alive; }
	bool isVisible() const						{ return visible; }

	virtual void setVisible(bool vis)
	{
		visible = vis;
		visible ? RegisterRenderItem(renderItem) : DeregisterRenderItem(renderItem);
	}

	void toggleVisible()						{ visible = !visible; }
	void kill()									{ alive = false; }

	virtual Vector3 getPosition()				{ return pose->p; }
	virtual PxQuat getRotation()				{ return pose->q; }
	virtual float getSize() const				{ return size; }
	virtual float getMass() const				{ return mass; }
	virtual Vector3 getVel()					{ return vel; }
	//string& getName()							{ return name; }

	virtual void setPosition(const Vector3 pos) { pose->p = pos; }
	virtual void setRotation(const PxQuat rot)	{ pose->q = rot; }
	virtual void setSize(float siz)				{ size = siz; }
	virtual void setMass(float mas)				{ mass = mas; }
	virtual void setVel(const Vector3& vel)		{ this->vel = vel; }

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

	virtual void addForce(float x, float y, float z) { }
	virtual void addForce(const Vector3& fc) { }
};
