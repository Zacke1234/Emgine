#pragma once
#include "glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object/Object.h"
#include <vector>



struct LightData {

	/*	glm::vec3 PointLight;
		glm::vec3 DirectionalLight;
		glm::vec3 SpotLight;*/
		//int lightType = 0; // 0 = point, 1 = directional, 2 = spot.
		enum LightType {
			Null, Point, Directional, Spot
		};
		float ambientStrength = 0.1f;
		glm::vec3 lightPos;
		enum LightType PointLight = Point;
		enum LightType DirLight = Directional;
		enum LightType SpotLight = Spot;
		enum LightType LightVar;
		
private:
	

public:
	void InitialiseLightData(Shader* shader, LightData* aLightData);

	
};


class Lighting
{
public:
	
	 
	
	Lighting();
	//std::vector<LightData> Lightdata;
	void Use(Camera* aCamera, Shader* aShader);
	//LightData* myLightData
	

	
	
};

