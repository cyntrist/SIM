#include "ForceGenerator.h"
#include "Scene.h"

#include <cmath>

void ForceGenerator::generateRadiusSphere()
{
	if (!active) return;

	if (radius <= 0)
		return;

	if (!widget || !widget->isVisible())
	{
		if (widget == nullptr)
		{
			widget = new Widget(scene, origen, radius);
			scene->addGameObject(widget);
		}
		else widget->setVisible(true);
	}

	widget->changeShape(CreateShape(PxSphereGeometry(radius)));
}

ForceGenerator::ForceGenerator(Vector3 org, Scene* scn, bool act) : origen(org), scene(scn), active(act)
{
	if (act) generateRadiusSphere();
}

ForceGenerator::~ForceGenerator()
{
	if (widget != nullptr) 
		widget->setVisible(false);
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





/// GRAVEDAD
Vector3 GravityGenerator::generateForce(GameObject& obj)
{
	return gravity * obj.getMass();
}

/// VIENTO
Vector3 WindGenerator::generateForce(GameObject& obj)
{
	// calculo de la fuerza en un viento no turbulento
	Vector3 force = k1 * (vientoVel - obj.getVel()) + k2;
	return force;
}

/// TORBELLINO
Vector3 WhirlwindGenerator::generateForce(GameObject& obj)
{
	Vector3 partPos = obj.getPosition();
	int sentido = clockwise ? -1 : 1;
	//calculo de la fuerza en torbellino
	Vector3 force = k * Vector3(
		-(partPos.z - origen.z) * sentido,
		50 - (partPos.y - origen.y),
		(partPos.x - origen.x) * sentido
);

	force -= obj.getVel();

	return force;
}

/// EXPLOSION
void ExplosionGenerator::startGenerating()
{
	active = true;
	simuleTime = 0;
}

Vector3 ExplosionGenerator::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0);

	if (!active || simuleTime < 0 || simuleTime >= 4 * tau) return force;
	
	float r = (obj.getPosition() - origen).magnitude(); // distancia al centro de la explosion
	// si la distancia es menor que el radio la fuerza es 0
	if (r >= radius) return force; // creo que esto no hace falta, porque si entra al metodo es porque r<radious

	force = k / r * r * (obj.getPosition() - origen) * exp(-simuleTime / tau);
	return force;
}

/// MUELLES
Vector3 SpringGenerator::generateForce(GameObject& obj)
{
	Vector3 dir = origen - obj.getPosition(); // posicion del ancla - la del objeto (vector de la fuerza)
	float actLength = dir.magnitude(); // longitud actual de la fuerza muelle
	dir.normalize(); // direccion de la fuerza
	float diffLength = actLength - restingLength; // deformacion del muelle
	Vector3 force = dir * k * diffLength; // calculo de la fuerza

	return force;
}

/// GOMAS
Vector3 RubberGenerator::generateForce(GameObject& obj)
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

/// FLOTACION
Vector3 FlotationGenerator::generateForce(GameObject& object)
{
	double height = object.getSize() * 2,
	      h = object.getPosition().y,
	      h0 = origen.y,
	      immersed,
	      density = k,
	      volume = pow(object.getSize() * 2, 3);

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

	force.y = density * volume * immersed * 9.8;

	return force;
}
