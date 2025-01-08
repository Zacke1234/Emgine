#include "Lighting.h"
#include <glad.h>
#include <glfw3.h>
#include "Cube.h"
#include "Shader.h"
#include <gtc/type_ptr.hpp>

//Cube* myCube;

Lighting::Lighting()
{
	
}

void Lighting::Use()
{
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	//glBindBuffer(GL_ARRAY_BUFFER, myCube->VBO);
	//set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Lighting::SetVec3(const char* texture, glm::vec3 aVec3)
{
	//glUniformMatrix4fv(glGetUniformLocation(myShader->ShaderProgram, texture), 1, GL_FALSE, glm::value_ptr(aVec3));
}
