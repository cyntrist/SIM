#pragma once
#include "GameObject.h"

class RigidBody : public GameObject
{
public:
	RigidBody();
};

class StaticRigidBody : public RigidBody
{
public:
	StaticRigidBody();

};

class DynamicRigidBody : public RigidBody
{
public:
	DynamicRigidBody();
};