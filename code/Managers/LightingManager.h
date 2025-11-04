#pragma once
#include <Lighting.h>
class LightingManager
{
public: 

	Lighting* DefaultLighting;

	LightData* CreateData(LightData* lightData);
	Lighting* Create(Lighting* lighting);
	void Destroy(Lighting* light, LightData* lightData);
	
};

