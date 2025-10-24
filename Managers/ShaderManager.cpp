#include "ShaderManager.h"

Shader* ShaderManager::InitDefaultShader()
{
	DefaultShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	return DefaultShader;
}

Shader* ShaderManager::Create(Shader* myShader)
{
	
	myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	DefaultShader = myShader;
	return myShader;
}

// C:\Users\zackarias.hager\source\repos\Emgine\Shader