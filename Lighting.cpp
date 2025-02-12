#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include "vector"

//Cube* myCube;



Lighting::Lighting()
{
	//glm::vec3(-1.3f, 1.0f, -1.5f)
	//LightingVertex vertex;
	vertex.position = { -1.0, -1.0, 0.0 }; { -1.0, 1.0, 0.0; }; { 1.0, 1.0, 0.0; }// first triangle
	{ -1.0, -1.0, 0.0; } { 1.0, 1.0, 0.0; } { 1.0, -1.0, 0.0; }; //second one
	vertex.uv = { 0.0, 0.0 }; { 0.0, 1.0; } { 1.0, 1.0; } { 0.0, 0.0; } { 1.0, 1.0; } { 1.0, 0.0; };
	vertex.normal = { 0, 0, 1 }; { 0, 0, 1; } { 0, 0, 1; } { 0, 0, 1; } { 0, 0, 1; } { 0, 0, 1; };
};


   
GLuint indicies[6] =
{
	0,
	1,
	2,
	0,
	2,
	3,
};

GLuint vertexBuffer = 1;

void Lighting::Initialise()
{
	// objLoader->temp_vertices.size()
	glGenBuffers(1, &vertexBuffer); // vertexBuffer is now the id of a new gl buffer

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind buffer to be modified in gl state

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		vertices.data(), GL_STATIC_DRAW);
	
	/*glBufferData(GL_ARRAY_BUFFER, objLoader->temp_vertices.size() * sizeof(Vertex),
		objLoader->temp_vertices.data(), GL_STATIC_DRAW);*/
	// done once
}

void Lighting::Use()
{
	//SetMatrix("", trans);
	glEnableVertexAttribArray(0); // vertex​

	//glEnableVertexAttribArray(1); // UVs​

	//glEnableVertexAttribArray(2); // normals


  	const int stride = 3 + 2 + 3; // 3 pos, 2 uv, 3 no rmal​
	const int StrideBytes = stride * sizeof(float);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, StrideBytes, (void*)0);
	/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, StrideBytes, (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, StrideBytes, (void*)(5 * sizeof(float)));*/

	GLuint indexBuffer = 1;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer); // bind it to be interacted with
	SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

	//Buffer in the new indices array

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indicies, 1);
}



void Lighting::SetMatrix(const char* texture, glm::mat4 MAT)
{
	glUniformMatrix4fv(glGetUniformLocation(LightingProgram, texture), 1, GL_FALSE, glm::value_ptr(MAT));
}

void Lighting::SetVec3(const char* texture, glm::vec3 aVec3)
{
	glUniformMatrix4fv(glGetUniformLocation(LightingProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec3));
}