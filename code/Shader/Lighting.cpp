#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>


std::vector<LightData*> lightsList;
//LightObject::LightEntities.size();
Camera* cameron = new Camera();
// 
// shadow mapping  
float near_plane = 1.0f, far_plane = 7.5f;
glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 lightSpaceMatrix =  lightProjection * lightView;
int lightSpaceMatrixLocation;

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};
std::string temp1 = "PLight[";
std::string temp2 = "PLight[";
std::string temp3 = "PLight[";


int PointLightShaderSetting(Shader* shader)
{
	
	
	
	for (int lObjs = 1; lObjs <= LightObject::LightEntities.size(); lObjs++)
	{
		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		
		shader->SetFloat("PLight[" + number + "].constant", 1.0f);
		shader->SetFloat("PLight[" + number + "].linear", 0.09f);
		shader->SetFloat("PLight[" + number + "].quadratic", 0.032f);
	
		temp1.append(number);
		temp2.append(number);
		temp3.append(number);
		
		
		std::string tempAmb = "].ambient";
		std::string tempDiff = "].diffuse";
		std::string tempSpec = "].specular";
		std::string ambient = temp1.append(tempAmb);
		std::string diffuse = temp2.append(tempDiff);
		std::string specular = temp3.append(tempSpec);

	
		shader->SetVec3(ambient.c_str(), glm::vec3(0.05f, 0.05f, 0.05f)); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), glm::vec3(0.8f, 0.8f, 0.8f));

		shader->SetVec3(specular.c_str(), glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetInt("NR_POINT_LIGHTS", lObjs);
		
		
	}

	
	return 0;
}

Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	
	shader->SetVec3("viewPos", aCamera->myPosition);
	//glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	
}

void LightData::InitialiseLightData(Shader* shader, LightData* aLightData, Camera* aCamera)
{
	switch (aLightData->LightVar)
	{
	case 0:
		
		//std::cout << "Null light" << std::endl;
		break;
	case 1:
		//std::cout << "Point light" << std::endl;
		

		GL_CHECK(shader->SetFloat("PLight.constant", 1.0f));
		GL_CHECK(shader->SetFloat("PLight.linear", 0.09f));
		GL_CHECK(shader->SetFloat("PLight.quadratic", 0.032f));

		shader->SetVec3("PLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("PLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("PLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("PLight.position", aLightData->lightPos);
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);

		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		PointLightShaderSetting(shader);
		shader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5, 0.31));
		shader->SetInt("material.diffuse", 1);
		shader->SetInt("material.specular", 1);
		shader->SetFloat("material.shininess", 32.0f);
		break;
	case 2:
		//std::cout << "Directional light" << std::endl;
		shader->SetVec3("Dlight.direction", aLightData->lightPos); // for directional light
		shader->SetVec3("Dlight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("Dlight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("Dlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		//shader->SetVec3("DLight.position", aLightData->lightPos);
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		//shader->SetVec3("viewPos", aCamera->myPosition);
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5, 0.61));
		shader->SetInt("material.diffuse", 1);
		shader->SetInt("material.specular", 1);
		shader->SetFloat("material.shininess", 100.0f);
		break;
	case 3:
		//std::cout << "Spot light" << std::endl;
		shader->SetVec3("Slight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("Slight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->SetVec3("Slight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("Slight.position", aLightData->lightPos);
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader->SetFloat("ambientStrength", ambientStrength);
		//shader->SetVec3("viewPos", aCamera->myPosition);
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetVec3("material.ambient", glm::vec3(1.0f, 1.5, 0.31));
		shader->SetInt("material.diffuse", 1);
		shader->SetInt("material.specular", 1);
		shader->SetFloat("material.shininess", 32.0f);
		break;
	default:
		std::cout << "Default" << std::endl;
		break;
	}

	//for (int l = 0; l < LightObject::LightEntities.size(); l++)
	//{	
	//	//LightObject::SelectedEntity = l;
	//	//std::string number = sizeof(lObjs);

	//	// I want to find each light entity and be able to tell if each one is a certain type of light, directional, spot, pointlight.
	//	//LightObject::LightEntities[l]->myLightData-
	//	




	//}
	
}


