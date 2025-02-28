#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"

Lighting::Lighting(const char* VertexPath, const char* FragmantPath)
{
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	ambientStrength = 0.1f;

	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmantShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCodeString = LoadLighting(VertexPath);
	const char* vertexCode = vertexCodeString.c_str();
	glShaderSource(vertexShader, 1, &vertexCode, NULL);

	glCompileShader(vertexShader);
	fragmantShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmantCodeString = LoadLighting(FragmantPath);
	const char* fragmantCode = fragmantCodeString.c_str();
	glShaderSource(fragmantShader, 1, &fragmantCode, NULL);

	glCompileShader(fragmantShader);
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmantShader);
	glLinkProgram(shaderProgram);
	LightingProgram = shaderProgram;

	int result;
	char Log[512];
	glGetShaderiv(fragmantShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmantShader, 512, NULL, Log);
		std::cout << "Failed to compile fragment shader \n" << Log << std::endl;
	}
}

GLuint vertexBuffer = 1;
glm::vec3 coral(1.0f, 0.5f, 0.31f);

void Lighting::UseLightingProgram()
{
	glUseProgram(LightingProgram);
}

void Lighting::SetMatrix(const char* transform, glm::mat4 aMatrix)
{
	glUniformMatrix4fv(glGetUniformLocation(LightingProgram, transform), 1, GL_FALSE, glm::value_ptr(aMatrix));
}

void Lighting::SetVec3(const char* texture, glm::vec3 aVec3)
{
	glUniformMatrix4fv(glGetUniformLocation(LightingProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec3));
}

void Lighting::SetVec4(const char* texture, glm::vec4 aVec4)
{
	glUniformMatrix4fv(glGetUniformLocation(LightingProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec4));
}

void Lighting::SetFloat(const std::string texcord, float aTexCord)
{
	glUniform1f(glGetUniformLocation(LightingProgram, texcord.c_str()), aTexCord);
}

std::string Lighting::LoadLighting(const char* aPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(aPath);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();
		shaderCode = shaderStream.str();

		return shaderCode;
	}
	catch (std::ifstream::failure e)
	{
		//std::cout << "Could not load shader file from path - " << aPath << "\n";
		return "";
	}
}


void Lighting::Use(Camera* aCamera, Shader* shader)
{
	shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec3("objectColor", coral);
	shader->SetVec3("lightPos", lightPos);
	shader->SetFloat("ambientStrength", ambientStrength);
	shader->SetMatrix("model", model);
	shader->SetVec3("viewPos", glm::vec3(1.0f, 1.0f, 1.0f));
}



