#pragma once
#include <string>
#include "Texture.h"
class TextureManager
{
public:
	Texture* Create(std::string fromPath);
};

