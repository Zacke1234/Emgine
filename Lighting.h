#pragma once
#include <vector>
#include <iostream>
#include "VirtualObject.h"


class Lighting
{
public:
	Lighting(const char* VertexPath, const char* FragmantPath);

	void Use(Camera* aCamera, Shader* aShader);

	void UseLightingProgram();

	void SetMatrix(const char* transform, glm::mat4 aMatrix);

	void SetVec3(const char* texture, glm::vec3 aVec3);

	void SetVec4(const char* texture, glm::vec4 aVec4);

	void SetFloat(const std::string, float aTexCord);

	std::string LoadLighting(const char* aPath);

	unsigned int LightingProgram;
	float ambientStrength = 0.1f;

	glm::vec3 lightPos;

	glm::mat4 model;
	
};

