#pragma once
#include <string>
#include "Shader.h"
class ShaderManager
{
public:
	Shader* Create(std::string fromPath);
};

