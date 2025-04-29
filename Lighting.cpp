#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"

// shadow mapping 
float near_plane = 1.0f, far_plane = 7.5f;
glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 lightSpaceMatrix = lightView;

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
	shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
	

	
}



