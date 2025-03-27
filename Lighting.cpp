#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"

Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec3("lightPos", lightPos);
	shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
	shader->SetFloat("ambientStrength", ambientStrength);
	shader->SetVec3("viewPos", glm::vec3(0, 0, 0));
}



