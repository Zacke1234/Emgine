#include "LightingManager.h"

Lighting* LightingManager::Create()
{
	Lighting* light = new Lighting();
	return light;
}

void LightingManager::Destroy(Lighting* light)
{
	Destroy(light);
}
