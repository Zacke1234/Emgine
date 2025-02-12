#pragma once
#include <vector>
#include <iostream>
#include "VirtualObject.h"

// phong shader

struct LightingVertex {
	/*float position[3];
	float uv[1];
	float normal[1];*/


	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	/*std::vector<float> position;
	std::vector<float> uv;
	std::vector<float> normal;*/
	
	// 8 floats, 32 bytes
};






class Lighting
{
public:
	Lighting();

	unsigned int lightVAO;

	void Use();

	void Initialise();

	void SetMatrix(const char* texture, glm::mat4 mat4);

	void SetVec3(const char* texture, glm::vec3 aVec3);

	float ambientStrength = 0.1f;

	std::vector<LightingVertex> vertices;

	/*glm::vec2 uv;
	glm::vec3 normal;*/
private:

	LightingVertex vertex;
	Cube* cube;
	ObjLoader* objLoader;
	Shader* shader;
	Camera* camera;
	VirtualObject* virtobj;
	unsigned int LightingProgram;
	
};

