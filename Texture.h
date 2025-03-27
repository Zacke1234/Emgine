#pragma once
class Texture
{
public:
	Texture(const char* aPath);

	bool IsValid() const { return TextureObject != 0; };


	int Width = 0;
	int Height = 0;

	unsigned int TextureObject = 0;
};

