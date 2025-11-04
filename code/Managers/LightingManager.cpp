#include "LightingManager.h"

LightData* LightingManager::CreateData(LightData* lightData)
{
	lightData = new LightData();
	
	//Lighting* light = new Lighting();
	//LightData::lightsList.push_back(lightdata);
	return lightData;
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
