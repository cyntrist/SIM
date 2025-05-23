#pragma once
#include "RenderUtils.hpp"
#include <iostream>

using namespace std;
using namespace physx;

class GameObject;
class ParticleGenerator;

struct ObjInfo
{
	GameObject* gameObject;
	ParticleGenerator* partGen;
};

inline void Log(const std::string& message)
{
#if _DEBUG
	std::cout << message << "\n";
#endif 
}
