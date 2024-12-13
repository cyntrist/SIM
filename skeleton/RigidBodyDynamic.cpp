﻿#include "RigidBodyDynamic.h"
#include "Scene.h"

RBDynamic::RBDynamic(string nam, Scene* scn, PxPhysics* gPhysics): RBActor(nam, scn, gPhysics)
{
	density = 10.0f;
	pose = new PxTransform({ 0,20,0 });
	actor = gPhysics->createRigidDynamic(*pose);
	actor->setLinearVelocity({ 0,0,0 });
	actor->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::updateMassAndInertia(*actor, density);
	actor->setMass(100);
	size = 10;
	//actor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);

	shape = CreateShape(PxBoxGeometry(size/2, size/2, size/2));
	actor->attachShape(*shape);
	renderItem = new RenderItem(shape, actor, { 0.8,0.8,0.8,1 });

}

RBDynamic::~RBDynamic()
{
}

void RBDynamic::setShape(PxShape* shp, float siz)
{
	RBActor::setShape(shp, siz);
	actor->attachShape(*shape);
}

void RBDynamic::setVisible(bool vis)
{
	RBActor::setVisible(vis);
	scene->setActorVisible(actor, vis);
}
