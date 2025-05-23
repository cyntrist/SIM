#pragma once
#include "RenderUtils.hpp"

using namespace std;
using namespace physx;

class ParticleGenerator;
class GameObject;

struct ObjInfo
{
	GameObject* gameObject;
	ParticleGenerator* partGen;
};

inline void Log(const string& message)
{
#if _DEBUG
	cout << message << "\n";
#endif 
}
