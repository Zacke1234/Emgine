#pragma once
#include <glfw3.h>
#include <glm.hpp>
#include "Shader.h"
#include "ObjLoader.h"
#include "VirtualObject.h"
#include "Texture.h"
class Cube
{
public:
	Cube();
	/*const float* someVertices, size_t aVertexSize, unsigned int* someIndices, size_t aIndexSize*/
	void Draw(Shader* myShader, VirtualObject* myVirtualObject, Camera* myCamera);

	void ApplyTexture(Texture* aTexture);

	void InitializeCube();

	//glm::mat4 MyTexture;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	//std::string Path; 

	size_t indexCount, vertexCount;

	

private:
	
};

