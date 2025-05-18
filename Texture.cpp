#include "Texture.h"
#include <glfw3.h>
#include <glad.h>
#include "stb_image.h"
#include <iostream>
#include "glm.hpp"


float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

Texture::Texture(const char* aPath)
{
	//std::cout << "texture" << "\n";
	//aPath = "Default 1.png";
	int Channels = 0;
	Width = 0;
	Height = 0;

	unsigned char* data = stbi_load(aPath, &Width, &Height, &Channels, 0);
	glGenTextures(1, &TextureObject);
	glBindTexture(GL_TEXTURE_2D, TextureObject);
	
	

	
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	if (data != NULL)
	{
		//std::cout << "data = true" << "\n";
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		msg = "Texture loaded in";
		//message->SendMessage(msg, 0);
	}
	
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}


