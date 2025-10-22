#pragma once
#include "glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object/Object.h"
#include <vector>


struct LightData {
		glm::vec3 PointLight;
		glm::vec3 DirectionalLight;
		glm::vec3 SpotLight;
		//int lightType = 0; // 0 = point, 1 = directional, 2 = spot.

		enum LightType {
			Null, Point, Directional, Spot
		};
		glm::vec3 lightPos;
		
};


class Lighting
{
public:
	std::vector<LightData*> lightdatas; // error 
	enum LightType light;

	Lighting();
	//std::vector<LightData> lightdata;
	void Use(Camera* aCamera, Shader* aShader);
	//LightData* myLightData
	float ambientStrength = 0.1f;

	
	
};

