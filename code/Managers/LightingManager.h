#pragma once
#include <Lighting.h>
class LightingManager
{
public: 
	Lighting* Create();
	void Destroy(Lighting* light);
};

