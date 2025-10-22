#pragma once
#include <string>
#include "Texture.h"
#include <vector>
class TextureManager
{
public:
	std::vector<Texture*> textures;
	Texture* Create(std::string name = "newtexture", std::string path_end = NULL);
	Texture* Find(std::string name);
};

