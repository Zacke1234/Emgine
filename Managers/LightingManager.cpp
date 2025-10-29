#include "LightingManager.h"

LightData* LightingManager::CreateData(LightData* lightData)
{
	LightData* lightdata = new LightData();
	//Lighting* light = new Lighting();
	//LightData::lightsList.push_back(lightdata);
	return lightdata;
}

Lighting* LightingManager::Create(Lighting* myLighting)
{
	myLighting = new Lighting();
	DefaultLighting = myLighting;
	
	return myLighting;
}

void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}
