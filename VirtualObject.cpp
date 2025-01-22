#include "VirtualObject.h"
#include "Shader.h"
#include "Cube.h"
#include "ObjLoader.h"
#include "MeshManager.h"
#include <cassert>
#include <glad.h>

//#include "Lighting.cpp"

std::vector<VirtualObject*> VirtualObject::Entities;
int VirtualObject::SelectedEntity;



//auto object = new VirtualObject(mesh, myTexture, myShader);
VirtualObject::VirtualObject()
{
	myCube = nullptr;
	myTexture = nullptr;
	MyShader = nullptr;
	myMesh = nullptr;
	//isCube = false;

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	//Name[255] = nullptr;
}

VirtualObject::VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn)
{
	//myCube = aCube;
	myTexture = aTexture;
	MyShader = aShader;
	myMesh = Mesh;
	//Name[255] = aName[255];
	this->namn = _namn;
	

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);

}

VirtualObject::VirtualObject(Cube* cube, Texture* aTexture, Shader* aShader)
{
	myTexture = aTexture;
	MyShader = aShader;
	myCube = cube;
	//Name[255] = aName[255];

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
}

void VirtualObject::SetCube(Cube& aCube)
{
	myCube = &aCube;
}

void VirtualObject::SetTexture(Texture& aTexture)
{
	myTexture = &aTexture;
}

void VirtualObject::SetShader(Shader& aShader)
{
	MyShader = &aShader;
}

void VirtualObject::SetMesh(Mesh& aMesh)
{
	myMesh = &aMesh;
}

void VirtualObject::SetName(std::string name)
{
	namn = name;
}

void VirtualObject::Draw(Camera* aCamera, Shader* myShader)
{
	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::translate(trans, Position);

	trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

	trans = glm::scale(trans, Scale);

	glActiveTexture(GL_TEXTURE0); // Activate the texture unit before binding texture
	glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

	MyShader->SetMatrix("transform", trans);
	MyShader->SetMatrix("view", aCamera->myView);
	MyShader->SetMatrix("projection", aCamera->projection);
	
	//
	
	//assert(VAO);
	if (myTexture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);   
	}

	//glBindVertexArray(myMesh->vertexbuffer);
	//
	//glDrawArrays(GL_TRIANGLES, 0, myMesh->data.size());
	glBindVertexArray(1);
	//// 36 for the cubes
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


	glBindTexture(GL_TEXTURE_2D, 0);
}

void VirtualObject::DrawObject(Camera* aCamera, Shader* myShader)
{
	
	assert(myMesh);
	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::translate(trans, Position);

	trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

	trans = glm::scale(trans, Scale);

	glActiveTexture(GL_TEXTURE0); // Activate the texture unit before binding texture
	glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

	MyShader->SetMatrix("transform", trans);
	MyShader->SetMatrix("view", aCamera->myView);
	MyShader->SetMatrix("projection", aCamera->projection);

	if (myTexture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject);
	}

	glBindVertexArray(myMesh->vertexbuffer);
	//
	glDrawArrays(GL_TRIANGLES, 0, myMesh->data.size());

	//myCube->DrawObject(myShader, this);

	glBindTexture(GL_TEXTURE_2D, 0);
}


