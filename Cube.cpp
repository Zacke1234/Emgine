#include "Cube.h"
#include <glad.h>
#include "Texture.h"
#include "Shader.h"
#include "VirtualObject.h"
#include <ext/matrix_transform.hpp>
#include "ObjLoader.h"
#include <cassert>    
#include "vector"
#include <glad.h>
#include "Physics.h"
using namespace std;

Texture* myTexture;


//float vertices[] = {
//	// positions          // colors           // texture coords
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//};

static float vertices[] = {
	// Positions           // Color    
	//     
	 // Front face
	 -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	0.0f, 1.0f,

	 // Back face			
	 -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
	 -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,	0.0f, 1.0f,

	  // Bottom face		
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,	1.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,	0.0f, 0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,	0.0f, 1.0f,

	  // Top face
	  -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	  -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	   // Left face
	   -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	   // Right face
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 1.0f
};


glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
static signed int indices[] = {
	// Front face
	0, 2, 1, 2, 0, 3,
	// Back face
	4, 6, 5, 6, 4, 7,
	// Bottom face
	8, 10, 9, 10, 8, 11,
	// Top face
	12, 14, 13, 14, 12, 15,
	// Left face
	16, 18, 17, 18, 16, 19,
	// Right face
	20, 22, 21, 22, 20, 23
};

Cube::Cube() // I need to learn to use constructors more (that can be said for everything in coding)
{	  

	vertexCount = 0;
	indexCount = 0;
	VBO = 0;
	EBO = 0;
	VAO = 0;
	

}


void Cube::InitializeCube()
{
	std::cout << "initialise cube" << "\n";
	IndicesSize = sizeof(indices);
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glBindVertexArray(VAO));
	
	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	//
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	
	EBO = 0;
	if (IndicesSize > 0)
	{
		GL_CHECK(glGenBuffers(1, &EBO));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		//
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
	}
	
	

	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));

	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(1));

	GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(2));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CHECK(glBindVertexArray(0));

}

void Cube::ApplyTexture(Texture* aTexture) 
{
	myTexture = aTexture;
}

void Cube::Draw(Shader* myShader, VirtualObject* myVirtualObject, Camera* aCamera)
{
	
	//std::cout << "draw cube" << "\n";
	//assert(VAO);

	GL_CHECK(glActiveTexture(GL_TEXTURE0)); // Activate the texture unit before binding texture
	
	if (myTexture != NULL && myTexture->IsValid())
	{
		GL_CHECK(glActiveTexture(GL_TEXTURE0));
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

		GL_CHECK(glActiveTexture(GL_TEXTURE1));
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);
	}
	
	//
	glm::mat4 trans = Math::identity4;

	trans = glm::translate(trans, myVirtualObject->Position);

	trans = glm::rotate(trans, myVirtualObject->Rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, myVirtualObject->Rotation.y, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, myVirtualObject->Rotation.z, glm::vec3(0, 0, 1));

	trans = glm::scale(trans, myVirtualObject->Scale);

	myShader->SetMatrix("transform", trans);
	myShader->SetMatrix("view", aCamera->myView);
	myShader->SetMatrix("projection", aCamera->projection);

	GL_CHECK(glBindVertexArray(VAO));
	if (IndicesSize > 0)
	{
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GL_CHECK(glDrawElements(GL_TRIANGLES, IndicesSize, GL_UNSIGNED_INT, (void*)0));
		GL_CHECK(glBindVertexArray(0));
	}
	
}



