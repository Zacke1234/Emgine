#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>

// shadow mapping  
float near_plane = 1.0f, far_plane = 7.5f;
glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 lightSpaceMatrix = lightView;

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	
	//LightType lightType;
	//enum LightData::LightType myEnum;
	/*glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f); 
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);*/
	//Object::Entities[0]->myLight = myLightData;
	//Object* lightObject = new Object(this->myLightData);
	//std::vector<Object*> lightObject2;
	//for (auto& l : lightObject2)
	//{
	//	
	//	//myLightData->lightType = lightObject;
	//}
	//auto LightType = Null;

	switch (light)
	{
	case 0: //NULL
		//std::cout << "Null light" << std::endl;
		shader->SetFloat("light.constant", 0.0f);
		shader->SetFloat("light.linear", 0.0f);
		shader->SetFloat("light.quadratic", 0.00f);

		shader->SetVec3("light.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->SetVec3("light.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->SetVec3("light.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		shader->SetVec3("lightColor", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->SetVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->SetVec3("objectColor", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		shader->SetVec3("viewPos", glm::vec3(0, 0, 0));
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetInt("material.diffuse", 0);
		shader->SetInt("material.specular", 0);
		break;
	case 1: //Point
		std::cout << "Point light" << std::endl;
		shader->SetFloat("PLight.constant", 1.0f);
		shader->SetFloat("PLight.linear", 0.09f);
		shader->SetFloat("PLight.quadratic", 0.032f);

		shader->SetVec3("PLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("PLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("PLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("lightPos", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		shader->SetVec3("viewPos", glm::vec3(0, 0, 0));
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);

		shader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5, 0.31));
		shader->SetInt("material.diffuse", 0);
		shader->SetInt("material.specular", 0);
		shader->SetFloat("material.shininess", 32.0f);

		shader->SetFloat("pointLights[0].constant", 1.0f);
		//std::cout << "light pos", myLightData->lightPos;
		// for point light
		break;
	case 2: // Directional
		std::cout << "Directional light" << std::endl;
		shader->SetVec3("Dlight.direction", glm::vec3(-0.2f, -1.0f, -0.3f)); // for directional light
		shader->SetVec3("Dlight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("Dlight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("Dlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("lightPos", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		shader->SetVec3("viewPos", glm::vec3(0, 0, 0));
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetInt("material.diffuse", 0);
		shader->SetInt("material.specular", 0);
		break;
	case 3: // Spot
		//std::cout << "Spot light" << std::endl;
		shader->SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("lightPos", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		shader->SetVec3("viewPos", glm::vec3(0, 0, 0));
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetInt("material.diffuse", 0);
		shader->SetInt("material.specular", 0);
		break;
		
	}
}



