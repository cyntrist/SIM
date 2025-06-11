#pragma once
#include "Widget.h"

class Scene;

class ForceGenerator
{
protected:
	float radius = 0;
	Vector3 origen = {0, 0, 0};
	Widget* widget = nullptr;
	Scene* scene = nullptr;
	PxVec4 color = { 0, 0, 1, 0.5 };
	bool active = true;
	void generateRadiusSphere();

public:
	ForceGenerator(Vector3 org, Scene* scn, bool active = true, PxVec4 color = { 0, 0, 1, 0.5 });
	virtual ~ForceGenerator();

	virtual Vector3 generateForce(GameObject& object) = 0;
	virtual bool onRadius(GameObject* obj);

	virtual void update(double delta)
	{
	}

	float getRadius() const { return radius; }
	void setRadius(float rad);
	void setActive(const bool act) { active = act; }

	void setColor(float r, float g, float b, float a) const
	{
		widget->setColor(Vector4(r, g, b, a));
		widget->changeShape(CreateShape(PxSphereGeometry(radius)));
	}

	void showWidget(bool show) const { if (widget != nullptr) widget->setVisible(show); }
};

class GravityGenerator : public ForceGenerator
{
protected:
	Vector3 gravity = {0, -9.8f, 0};

public:
	GravityGenerator(Vector3 org, Scene* scn, Vector3 grav) : ForceGenerator(org, scn), gravity(grav)
	{
	}

	Vector3 generateForce(GameObject& object) override;
};

class WindGenerator : public ForceGenerator
{
protected:
	//velocidad del viento
	Vector3 vientoVel = {0, 0, 0};
	//coeficientes de rozamiento
	float k1 = 10;
	Vector3 k2 = {0, 0, 0};

public:
	WindGenerator(Vector3 org, Scene* scn, Vector3 vVel = {0, 0, 0}) : ForceGenerator(org, scn), vientoVel(vVel)
	{
	}

	Vector3 generateForce(GameObject& object) override;
};

class WhirlwindGenerator : public ForceGenerator
{
protected:
	float k = 1; //coeficiente de rozamiento
	bool clockwise = false; // sentido de la rotacion
public:
	WhirlwindGenerator(Vector3 org, Scene* scn) : ForceGenerator(org, scn)
	{
	}
	void setClockwise(bool t) { clockwise = t; }
	Vector3 generateForce(GameObject& object) override;
};

class ExplosionGenerator : public ForceGenerator
{
protected:
	float k = 100;
	float tau = 0.05f;
	float ve = 125; // velocidad de expansion de la explosion
	float simuleTime = 0;
	bool sttc = false;

public:
	ExplosionGenerator(Vector3 org, Scene* scn, bool act = true)
		: ForceGenerator(org, scn, act) { simuleTime = 0; }

	void setPower(float p) { k = p; }
	void startGenerating();
	void setStatic(bool st) { sttc = st; }
	void update(double delta) override
	{
		if (!active) return;
		if (simuleTime <= 4 * tau)
		{
			simuleTime += delta;
			if (sttc) 
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
	}

	void setK(float K) { k = K; }
	bool onRadius(GameObject* obj) override { return obj == object; };

	Vector3 generateForce(GameObject& object) override;
};

class RubberGenerator : public ForceGenerator
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
	RubberGenerator(Scene* scn, float K, float restLength, GameObject* obj2, GameObject* obj1 = nullptr) :
		ForceGenerator({0, 0, 0}, scn), object1(obj1), object2(obj2), k(K), restingLength(restLength)
	{
	}

	bool onRadius(GameObject* part) override { return part == object2; };

	Vector3 generateForce(GameObject& object) override;
};

class FlotationGenerator : public ForceGenerator
{
protected:
	float k; // densidad del liquido

public:
	/// <param name="scn"> Scene</param>
	/// <param name="h"> altura del liquido </param>
	/// <param name="v"> volumen del liquido</param>
	/// <param name="K"> densidad del liquido</param>
	FlotationGenerator(Scene* scn, float h, float K) :
		ForceGenerator({0, h, 0}, scn), k(K)
	{
	}

	bool onRadius(GameObject* obj) override
	{
		if (obj) return obj->getPosition().y <= origen.y;
		return false;
	}

	Vector3 generateForce(GameObject& object) override;
};
