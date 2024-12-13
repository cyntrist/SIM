#include "ForceGenerator.h"
#include "Scene.h"

#include <cmath>

void ForceGenerator::generateRadiusSphere()
{
	if (radius <= 0)
		return;
	// si ya existe un render item, elimina el que esta y crea uno nuevo con el nuevo radio
	if (!widget)
	{
		widget = new Widget("RadioSphera", scene, origen, radius);

		scene->addGameObject(widget, nullptr);
	}

	widget->changeShape(CreateShape(PxSphereGeometry(radius)));
}

ForceGenerator::ForceGenerator(Vector3 org, Scene* scn) : origen(org), scene(scn)
{
	generateRadiusSphere();
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::onRadius(GameObject* obj)
{
	if (obj == nullptr) return false;
	if (radius == 0)
		return true;
	return (obj->getPosition() - origen).magnitude() <= radius;
}

void ForceGenerator::setRadius(float rad)
{
	radius = rad;
	generateRadiusSphere();
}

// ------- GENERADOR DE GRAVEDAD --------
Vector3 GravityGenerator::generateForce(GameObject& obj)
{
	return gravity * obj.getMass();
}


// ------- GENERADOR DE VIENTO --------
Vector3 VientoGenerador::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0);
	// calculo de la fuerza en un viento no turbulento
	force = k1 * (vientoVel - obj.getVel()) + k2;

	return force;
}

// ------- GENERADOR DE TORVELLINO -------
Vector3 TorbellinoGenerator::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0),
	        partPos = obj.getPosition();

	//calculo de la fuerza en torvellino
	force = k * Vector3(-(partPos.z - origen.z), 50 - (partPos.y - origen.y), partPos.x - origen.x);

	force -= obj.getVel();

	return force;
}

// -------- GENERADOR DE EXPLOSION --------
Vector3 ExplosionGenerator::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0);
	simuleTime;

	if (simuleTime < 0 || simuleTime >= 4 * tau) return force;


	// distancia al centro de la explosion
	float r = (obj.getPosition() - origen).magnitude();
	// si la distancia es menor que el radio la fuerza es 0
	if (r >= radius) return force; // creo que esto no hace falta, porque si entra al metodo es porque r<radius

	force = ((k / r * r) * (obj.getPosition() - origen)) * exp(-simuleTime / tau);


	return force;
}

// ------- MUELLES -------
Vector3 SpringGenerator::generateForce(GameObject& obj)
{
	Vector3 force{0, 0, 0};

	// largura actual del muelle
	Vector3 dir = origen - obj.getPosition();
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restingLength;

	// calculo de la fuerza
	force = dir * k * difflenth;

	//cout << force.y << endl;
	return force;
}

// ------ GOMA ELASTICA ------
Vector3 GomaGenerator::generateForce(GameObject& obj)
{
	Vector3 position1 = object1->getPosition();
	Vector3 force{0, 0, 0};

	// largura actual del muelle
	Vector3 dir = position1 - obj.getPosition();
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restingLength;
	if (difflenth <= 0) difflenth = 0;
	// calculo de la fuerza
	force = dir * k * difflenth;

	// aplica la fueza a ambos extremos del muelle
	object1->addForce(-force);
	return force;
}

// ------ FLOTACION -----
Vector3 FlotationGenerator::generateForce(GameObject& particle)
{
	float height = particle.getSize() * 2,
	      h = particle.getPosition().y,
	      h0 = origen.y,
	      immersed = 0,
	      liquidDensity = k,
	      volume = pow(particle.getSize() * 2, 3);

	if (h - h0 > height * 0.5)
	{
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5)
	{
		immersed = 1.0;
	}
	else
	{
		immersed = (h0 - h) / height + 0.5;
	}


	Vector3 force{0, 0, 0};


	// calculo de la fuerza
	force.y = liquidDensity * volume * immersed * 9.8;

	// aplica la fueza a ambos extremos del muelle
	return force;
}
