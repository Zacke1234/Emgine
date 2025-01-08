#include <string>
#include <glm.hpp>
#pragma once
class Shader
{
public:
	Shader(const char* VertexPath, const char* FragmantPath);

	void UseShader();

	void SetMatrix(const char* transform, glm::mat4 aMatrix);

	/*void SetView(const char* view, glm::mat4 aView);

	void SetProjection(const char* projection, glm::mat4 aProjection)*/; // deadass why did i make these when i could have just reaused the SetMatrix method, brainlet

	void SetVec2(const char* texture, glm::vec2 aVec2);

	void SetVec3(const char* texture, glm::vec3 aVec3);

	void SetFloat(const std::string, float aTexCord);

	//void SetSampler2D(const char* sampler, );

	std::string LoadShader(const char* aPath);

	unsigned int ShaderProgram;
private:
	
};