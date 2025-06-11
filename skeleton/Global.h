#pragma once
#include "RenderUtils.hpp"
#include <iostream>

using namespace std;
using namespace physx;

class GameObject;
class ParticleGenerator;

inline void Log(const std::string& message)
{
#if _DEBUG
	std::cout << message << "\n";
#endif 
}

inline PxVec4 hsvToRgb(float h, float s = 1.0f, float v = 1.0f, float a = 1.0f)
{ // esto no lo he hecho yo, lo he sacado de: https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72
	float c = v * s;
	float x = c * (1 - std::fabs(fmod(h / 60.0f, 2) - 1));
	float m = v - c;
	float r, g, b;

	if (h < 60) { r = c; g = x; b = 0; }
	else if (h < 120) { r = x; g = c; b = 0; }
	else if (h < 180) { r = 0; g = c; b = x; }
	else if (h < 240) { r = 0; g = x; b = c; }
	else if (h < 300) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }

	return { r + m, g + m, b + m, a };
}