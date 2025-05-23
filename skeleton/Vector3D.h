#pragma once
#include <cmath>

class Vector3D
{
	Vector3D() = default;
	Vector3D(double a, double b, double c) : x(a), y(b), z(c) { mod = module(); }

	// operadores
	void operator+(Vector3D& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	void operator-(Vector3D& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	void operator*(double a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
	}

	void operator*(Vector3D& v)
	{
		getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
	}

	void operator=(Vector3D& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//metodos
	void normalize()
	{
		this->x * 1 / this->mod;
		this->y * 1 / this->mod;
		this->z * 1 / this->mod;
		this->mod = module();
	}

	double module()
	{
		return sqrt(pow(2.0, x) + pow(2.0, y) + pow(2.0, z));
	}

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	double getModule() const { return mod; }

double x, y, z;
	double mod;
};
