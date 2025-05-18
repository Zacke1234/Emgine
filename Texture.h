#include "Message.h"
#pragma once
class Texture
{
public:
	Texture(const char* aPath);

	bool IsValid() const { return TextureObject != 0; };

	std::string msg;
	//Message* message = new Message(msg);
	
	int Width = 0;
	int Height = 0;

	unsigned int TextureObject = 0;
};

