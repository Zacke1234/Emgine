#include "Texture.h"
#include <glfw3.h>
#include <glad.h>
#include "stb_image.h"
#include <iostream>
#include "glm.hpp"

#pragma once
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

Texture::Texture(const char* aPath)
{
	msg = "";
	//std::cout << "texture" << "\n";
	//aPath = "Default 1.png";
	int Channels = 0;
	Width = 1920;
	Height = 1080;
	
	unsigned char* data = stbi_load(aPath, &Width, &Height, &Channels, 0);
	glGenTextures(1, &TextureObject);
	glBindTexture(GL_TEXTURE_2D, TextureObject);
	
	//Shadows
	

	if (data != NULL)
	{
		//std::cout << "data = true" << "\n";
		glGenFramebuffers(1, &depthMapFBO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, TextureObject, 0);
		/*glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);*/
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glGenerateMipmap(GL_TEXTURE_2D);

		

		//glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		// configure shader and matrices
		// render scene
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//
		//glViewport(0, 0, Width, Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, TextureObject);


		msg = "Texture loaded in";
		//message->SendMessage(msg, 0);
	}
	
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}


