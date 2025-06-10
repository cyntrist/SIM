#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Scene.h"
#include "SceneManager.h"

std::string display_text = "Cynthia Tristan Alvarez";
std::string level_won_2_text = "";
std::string level_won_1_text = "";
std::string controls_1_text = "Flechas ARR/ABJ: Cambiar de plancha";
std::string controls_2_text = "Flechas IZQ/DER: Girar planchas";
std::string controls_3_text = "CTRL / SHIFT + Flechas IZQ/DER: Girar planchas mas rapido o mas lento";



using namespace physx;

PxDefaultAllocator gAllocator;
PxDefaultErrorCallback gErrorCallback;

PxFoundation* gFoundation = nullptr;
PxPhysics* gPhysics = nullptr;


PxMaterial* gMaterial = nullptr;

PxPvd* gPvd = nullptr;

PxDefaultCpuDispatcher* gDispatcher = nullptr;
PxScene* gScene = nullptr;
ContactReportCallback gContactReportCallback;

std::vector<Particle*> mParticles;

SceneManager* sm = nullptr;
RenderItem *xRenderItem = nullptr, *yRenderItem = nullptr, *zRenderItem = nullptr;
PxTransform x, y, z;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	sm = new SceneManager(gPhysics, gScene);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for (const auto p : mParticles)
		p->integrate(t);

	if (sm != nullptr)
	{
		sm->update(t);
		if (sm->getWon())
		{
			level_won_1_text = "!Bien hecho!";
			level_won_2_text = "Suerte en el siguiente :^)";
		}
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	for (auto p : mParticles)
	{
		delete p;
		p = nullptr;
	}
}

// Function called when a key is pressed
void keyPress(unsigned char key, Camera* camera)
{
	PX_UNUSED(camera);

	sm->keyPressed(key, camera->getTransform());
}

void specialKeyPress(int key, Camera* camera)
{
	PX_UNUSED(camera);

	sm->specialKeyPressed(key, camera->getTransform());
}

void onCollision(PxActor* actor1, PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
