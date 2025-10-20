#include "ShaderManager.h"

Shader* ShaderManager::Create(Shader* myShader = NULL)
{
	myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	return nullptr;
}