#include "Cube.h"
#include <glad.h>
#include "Texture.h"
#include "Shader.h"
#include "VirtualObject.h"
#include <ext/matrix_transform.hpp>
#include "ObjLoader.h"
#include <cassert>
#include "vector"
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
	 -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,0.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,0.0f, 1.0f,

	 // Back face			
	 -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,1.0f, 1.0f,
	 -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,0.0f, 1.0f,

	  // Bottom face		
	  -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,1.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,1.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 0.0f,
	  -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 1.0f,

	  // Top face
	  -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,1.0f, 1.0f,
	  -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,0.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,0.0f, 1.0f,

	   // Left face
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,1.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f, 1.0f,

	   // Right face
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f
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
static unsigned int indices[] = {
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
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}



void Cube::InitializeObjectFile(Mesh* myMesh)
{
	/*if (myObjLoader->temp_vertices.empty() && myObjLoader->temp_faces.empty())
	{
		std::cout << "Empty vertices / faces" << std::endl;

		return;
	}*/

	//Mesh* myMesh = new Mesh();

	Vertex myVertex;
	Face myFace;
	ApplyTexture(myTexture);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	myMesh->vertexbuffer = VBO;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//indexCount = myMesh->faces.size();
	
	glBufferData(GL_ARRAY_BUFFER, myMesh->data.size() * sizeof(float), &myMesh->data[0], GL_STATIC_DRAW);
	// size / length

	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//glBufferData(GL_ARRAY_BUFFER, myMesh->data.size() * sizeof(float), &myMesh->data[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}
void Cube::ApplyTexture(Texture* aTexture) // the hell does this even do? sets mytexure to atexture? ?????????????????
{
	myTexture = aTexture;
}
void Cube::Draw(Shader* myShader, VirtualObject* myVirtualObject)
{
	
	
	//assert(VAO);
	if (myTexture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);
	}
	glBindVertexArray(VAO);
	// 36 for the cubes
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Cube::DrawObject(Shader* myShader, VirtualObject* myVirtualObject)
{
	//assert(VAO);
	if (myTexture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);
	}
	glBindVertexArray(VAO);
	// indexCount for the objects 
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

