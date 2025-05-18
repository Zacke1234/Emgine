#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "VirtualObject.h"
#include <glfw3.h>
#include <glm.hpp>

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
	/*static unsigned int &indices[];*/
	
	

private:
	int IndicesSize = 0;
};

