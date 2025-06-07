#include "RigidBodyGenerator.h"

#include "Level.h"

RigidBodyGenerator::RigidBodyGenerator(Vector3 org, int stNpart, PxPhysics* gphys, PxScene* gscn, 
                                       RigidBodySystem* partsys, Level* scn, double min, double max)
    : gphys(gphys), gscn(gscn), origen(org), system(partsys), maxGameObjects(stNpart),
	level(scn), minLife(min), maxLife(max)
{
}

void RigidBodyGenerator::update(double t)
{
    if (mayGenerate())
        generateBody(t);
}

void RigidBodyGenerator::generateBody(double t)
{
    PxVec3 volumen = { 1, 1, 1 };

    auto drb1 = new DynamicRigidBody(
        scene, gphys, gscn,
        false, SPHERE, volumen, 
        origen, velocity,
        0, 30
    );
    
    drb1->setColor(color);
    drb1->setDensity(density);
    drb1->setMass(10);
    drb1->setVisible(true);
    scene->addGameObject(drb1);

    addNumBodies(1);
    //level->generateBody();
}

bool RigidBodyGenerator::mayGenerate()
{
    if (nGameObjects >= maxGameObjects) 
        return false;
    counter += 1;
    if (counter >= timer)
    {
        counter = 0;
        return true;
    }
    return false;
}
