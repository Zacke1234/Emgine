#pragma once
#include <string>
#include "Collider.h"
class ColliderManager
{
public:
	Collider* Create(Collider* myColl);
	CubeCollider* planeColl;
	CubeCollider* cubeColl;
	SphereCollider* sphereColl;
};

