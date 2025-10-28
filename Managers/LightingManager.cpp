#include "LightingManager.h"

LightData* LightingManager::CreateData()
{
	LightData* lightdata = new LightData();
	//Lighting* light = new Lighting();
	//LightData::lightsList.push_back(lightdata);
	return lightdata;
}

Lighting* LightingManager::Create()
{
	Lighting* light = new Lighting();
	return light;
}

void LightingManager::Destroy(Lighting* light)
{
	Destroy(light);
}
