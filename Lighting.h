#pragma once
#include <vector>
#include <iostream>
#include "VirtualObject.h"

struct LightData {
	glm::vec3 PointLight;
	glm::vec3 DirectionalLight;
	glm::vec3 SpotLight;
};

class Lighting
{
public:
	Lighting();

	void Use(Camera* aCamera, Shader* aShader);

	float ambientStrength = 0.1f;

	glm::vec3 lightPos;
	
};

