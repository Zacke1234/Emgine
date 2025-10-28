#pragma once
#include <Lighting.h>
class LightingManager
{
public: 
	LightData* CreateData();
	Lighting* Create();
	void Destroy(Lighting* light);
};

