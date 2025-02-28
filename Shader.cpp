#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.hpp>


std::string Shader::LoadShader(const char* aPath)
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

Shader::Shader(const char* VertexPath, const char* FragmantPath)
{

	//"../Shader/FragmentShader_1.glsl"
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmantShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCodeString = LoadShader(VertexPath);
	const char* vertexCode = vertexCodeString.c_str();
	glShaderSource(vertexShader, 1, &vertexCode, NULL);

	glCompileShader(vertexShader);
	fragmantShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmantCodeString = LoadShader(FragmantPath);
	const char* fragmantCode = fragmantCodeString.c_str();
	glShaderSource(fragmantShader, 1, &fragmantCode, NULL);

	glCompileShader(fragmantShader);
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmantShader);
	glLinkProgram(shaderProgram);
	ShaderProgram = shaderProgram;

	int result;
	char Log[512];
	glGetShaderiv(fragmantShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmantShader, 512, NULL, Log);
		std::cout << "Failed to compile fragment shader \n" << Log << std::endl;
	}

}

void Shader::UseShader()
{
	glUseProgram(ShaderProgram);
}

void Shader::SetMatrix(const char* transform, glm::mat4 aMatrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, transform), 1, GL_FALSE, glm::value_ptr(aMatrix));
}

void Shader::SetVec2(const char* texture, glm::vec2 aVec2)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec2));
}
void Shader::SetVec3(const char* texture, glm::vec3 aVec3)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec3));
}
void Shader::SetVec4(const char* texture, glm::vec4 aVec4)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec4));
}
void Shader::SetFloat(const std::string texcord, float aTexcord)
{
	glUniform1f(glGetUniformLocation(ShaderProgram, texcord.c_str()), aTexcord);
}