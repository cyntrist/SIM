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
