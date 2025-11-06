
//using namespace std;
#pragma once
#include <string>
#include <glad.h>



class Texture
{
public:
	Texture(const char* aPath);

	bool IsValid() const { return TextureObject != 0; };

	std::string msg;
	//Message* message = new Message(msg);
	std::string name;
	int Width = 0;
	int Height = 0;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int TextureObject = 0;
	unsigned int depthMapFBO;

	
};

