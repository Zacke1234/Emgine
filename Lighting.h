#pragma once
#include <glm.hpp>


class Lighting
{
public:
	Lighting();

	unsigned int lightVAO;

	void Use();

	void SetVec3(const char* texture, glm::vec3 aVec3);
};

