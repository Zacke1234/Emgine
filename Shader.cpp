#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.hpp>
#include "VirtualObject.h"


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
	GL_CHECK(glShaderSource(vertexShader, 1, &vertexCode, NULL));

	GL_CHECK(glCompileShader(vertexShader));
	fragmantShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmantCodeString = LoadShader(FragmantPath);
	const char* fragmantCode = fragmantCodeString.c_str();
	GL_CHECK(glShaderSource(fragmantShader, 1, &fragmantCode, NULL));

	GL_CHECK(glCompileShader(fragmantShader));
	shaderProgram = glCreateProgram();

	GL_CHECK(glAttachShader(shaderProgram, vertexShader));
	GL_CHECK(glAttachShader(shaderProgram, fragmantShader));
	GL_CHECK(glLinkProgram(shaderProgram));
	ShaderProgram = shaderProgram;

	int result;
	int vertexResult;
	char Log[512];
	GL_CHECK(glGetShaderiv(fragmantShader, GL_COMPILE_STATUS, &result));
	GL_CHECK(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexResult));
	if (!result)
	{
		GL_CHECK(glGetShaderInfoLog(fragmantShader, 512, NULL, Log));
		std::cout << "Failed to compile fragment shader \n" << Log << std::endl;
	}
	if (!vertexResult)
	{
		GL_CHECK(glGetShaderInfoLog(vertexShader, 512, NULL, Log));
		std::cout << "Failed to compile vertex shader \n" << Log << std::endl;
	}
}

void Shader::UseShader()
{
	GL_CHECK(glUseProgram(ShaderProgram));
}

void Shader::SetMatrix(const char* transform, glm::mat4 aMatrix)
{
	GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, transform), 1, GL_FALSE, glm::value_ptr(aMatrix)));
}

void Shader::SetVec2(const char* texture, glm::vec2 aVec2)
{
	GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec2)));
}
void Shader::SetVec3(const char* texture, glm::vec3 aVec3)
{
	GL_CHECK(glUniform3fv(glGetUniformLocation(ShaderProgram, texture), 1, glm::value_ptr(aVec3)));
}
void Shader::SetVec4(const char* texture, glm::vec4 aVec4)
{
	GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec4)));
}
void Shader::SetFloat(const std::string texcord, float aTexcord)
{
	GL_CHECK(glUniform1f(glGetUniformLocation(ShaderProgram, texcord.c_str()), aTexcord));
}
void Shader::SetInt(const std::string depth, int aInt)
{
	glUniform1i(glGetUniformLocation(ShaderProgram, depth.c_str()), aInt);
}