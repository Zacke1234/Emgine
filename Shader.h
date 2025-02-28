#include <string>
#include <glm.hpp>
#pragma once
class Shader
{
public:
	Shader(const char* VertexPath, const char* FragmantPath);

	void UseShader();

	void SetMatrix(const char* transform, glm::mat4 aMatrix);

	void SetVec2(const char* texture, glm::vec2 aVec2);

	void SetVec3(const char* texture, glm::vec3 aVec3);

	void SetVec4(const char* texture, glm::vec4 aVec4);

	void SetFloat(const std::string, float aTexCord);

	std::string LoadShader(const char* aPath);

	unsigned int ShaderProgram;
private:
	
};