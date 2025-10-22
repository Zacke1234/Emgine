#include "TextureManager.h"
#include <iostream>
Texture* TextureManager::Create(std::string name, std::string path_end)
{
	std::string path = "C:\\Users\\zackarias.hager\\source\\repos\\Emgine\\Emgine\\resource\\textures\\";
	Texture* new_texture = new Texture((path + path_end).c_str());
	new_texture->name = name;
	textures.push_back(new_texture);
	std::cout << "Texture created: " << name << " from path: " << path + path_end << "\n";
	return new_texture;
}


Texture* TextureManager::Find(std::string name) {
	for (Texture* texture : textures)
		{
		if (texture->name == name)
			{
			return texture;
			std::cout << "Texture found: " << name << "\n";
			}
		}
	std::cout << "Texture not found: " << name << "\n";
	return nullptr;
}