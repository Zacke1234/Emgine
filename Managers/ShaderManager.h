#pragma once
#include <string>
#include "Shader.h"
class ShaderManager
{
public:

	Shader* DefaultShader;
	Shader* InitDefaultShader();

	Shader* Create(Shader* myShader);
};

