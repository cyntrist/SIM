#pragma once
#include "Particle.h"
#include "Widget.h"

class Scene;

class ForceGenerator
{
protected:
	// Propiedades inicio
	float radius = 0;
	Vector3 origen = {0, 0, 0};
	// Representacion de la zona de afectacion
	Widget* widget = nullptr;
	Scene* scene = nullptr;

	void generateRadiusSphere();

public:
	ForceGenerator(Vector3 org, Scene* scn);
	virtual ~ForceGenerator() = 0;


	virtual Vector3 generateForce(GameObject& object) = 0;
	virtual bool onRadius(GameObject* obj);

	virtual void update(double delta)
	{
	};

	void setRadius(float rad);
};

// ------- GENERADOR DE GRAVEDAD --------
class GravityGenerator : public ForceGenerator
{
protected:
	//aceleracion de la gravedad
	Vector3 gravity = {0, -9.8, 0};

public:
	GravityGenerator(Vector3 org, Scene* scn, Vector3 grav) : ForceGenerator(org, scn), gravity(grav)
	{
	};


	Vector3 generateForce(GameObject& object) override;
};

class VientoGenerador : public ForceGenerator
{
protected:
	//velocidad del viento
	Vector3 vientoVel = {0, 0, 0};
	//coheficientes de rozamiento
	float k1 = 10;
	Vector3 k2 = {0, 0, 0};

public:
	VientoGenerador(Vector3 org, Scene* scn, Vector3 vVel = {0, 0, 0}) : ForceGenerator(org, scn), vientoVel(vVel)
	{
	};

	Vector3 generateForce(GameObject& object) override;
};

class TorbellinoGenerator : public ForceGenerator
{
protected:
	//coheficiente de rozamiento
	float k = 1;

public:
	TorbellinoGenerator(Vector3 org, Scene* scn) : ForceGenerator(org, scn)
	{
	};


	Vector3 generateForce(GameObject& object) override;
};

class ExplosionGenerator : public ForceGenerator
{
protected:
	//potencia de la explosion
	float k = 100;
	float tau = 0.05;
	float ve = 125; // velocidad de expansion de la explosion
	float simuleTime = 0;

public:
	ExplosionGenerator(Vector3 org, Scene* scn) : ForceGenerator(org, scn) { simuleTime = 0; };

	~ExplosionGenerator() override
	{
	};

	// Settea la potencia de la explosion
	void setPotencia(float p) { k = p; };

	void startGenerate()
	{
		simuleTime = 0;
	};

	void update(double delta) override
	{
		if (simuleTime <= 4 * tau)
		{
			simuleTime += delta;
			setRadius(ve * simuleTime);
		}
	}

	Vector3 generateForce(GameObject& object) override;
};

class SpringGenerator : public ForceGenerator
{
protected:
	GameObject* object = nullptr;

	float k;
	float restingLength;

public:
	/// <param name="K"> Constante de elasticidad</param>
	/// <param name="restLength"> Largo muelle reposo</param>
	/// <param name="part">Particula afectada</param>
	SpringGenerator(Vector3 anch, Scene* scn, float K, float restLength, GameObject* obj) :
		ForceGenerator(anch, scn), object(obj), k(K), restingLength(restLength)
	{
	};

	~SpringGenerator() override
	{
	};

	void setK(float K) { k = K; }
	bool onRadius(GameObject* obj) override { return obj == object; };

	Vector3 generateForce(GameObject& object) override;
};

class GomaGenerator : public ForceGenerator
{
protected:
	GameObject* object1 = nullptr;
	GameObject* object2 = nullptr;

	float k;
	float restingLength;

public:
	/// <param name="K"> Constante de elasticidad</param>
	/// <param name="restLength"> Largo muelle reposo</param>
	/// <param name="part2">Particula afectada</param>
	/// <param name="part1">Particula(ancla)</param>
	GomaGenerator(Scene* scn, float K, float restLength, GameObject* obj2, GameObject* obj1 = nullptr) :
		ForceGenerator({0, 0, 0}, scn), object1(obj1), object2(obj2), k(K), restingLength(restLength)
	{
	};

	bool onRadius(GameObject* part) override { return part == object2; };

	Vector3 generateForce(GameObject& object) override;
};

class FlotationGenerator : public ForceGenerator
{
protected:
	float k; // densidad del liquido

public:
	/// <param name="h"> superficie del liquido </param>
	/// <param name="scn"> Scene</param>
	/// <param name="K"> densidad del liquido</param>
	FlotationGenerator(float h, Scene* scn, float K) :
		ForceGenerator({0, h, 0}, scn), k(K)
	{
	};


	bool onRadius(GameObject* obj) override { if (obj) return obj->getPosition().y <= origen.y; };

	Vector3 generateForce(GameObject& object) override;

	void setDamping(GameObject* obj);
};
