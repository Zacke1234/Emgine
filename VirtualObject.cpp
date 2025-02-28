#include "VirtualObject.h"
#include "Shader.h"
#include "Cube.h"
#include "ObjLoader.h"
#include "MeshManager.h"
#include <cassert>
#include <glad.h>
#include "Collider.h"
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
	myCollider = nullptr;
	//isCube = false;

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	//Name[255] = nullptr;
}

VirtualObject::VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll)
{
	//myCube = aCube;
	myTexture = aTexture;
	MyShader = aShader;
	myMesh = Mesh;
	//Name[255] = aName[255];
	this->namn = _namn;
	IsMesh = true;
	myCollider = coll;
	

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);

}

VirtualObject::VirtualObject(Cube* cube, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll)
{
	myTexture = aTexture;
	MyShader = aShader;
	myCube = cube;
	//Name[255] = aName[255];
	this->namn = _namn;
	IsCube = true;


	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
}

VirtualObject::~VirtualObject()
{
	delete myMesh, myCube;
}

void VirtualObject::SetCube(Cube& aCube)
{
	myCube = &aCube;
}

void VirtualObject::CreateCube(Cube& aCube)
{
	
}

void VirtualObject::SetTexture(Texture& aTexture)
{
	myTexture = &aTexture;
}

void VirtualObject::SetShader(Shader& aShader)
{
	MyShader = &aShader;
}

void VirtualObject::CreateMesh(Mesh& aMesh) 
{
	
	aMesh = myObjLoader->ObjParser("./teapot.obj"); //teapot.obj
	
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
	if (IsCube)
	{
		DrawCube(aCamera, myShader);
	}
	else if(IsMesh)
	{
		DrawObject(aCamera, myShader);
	}
}

void VirtualObject::DrawCube(Camera* aCamera, Shader* myShader)
{
	myCube->Draw(myShader, this, aCamera);
}

void VirtualObject::DrawObject(Camera* aCamera, Shader* myShader)
{
		
		//std::cout << "draw object in virtualobject" << "\n";
		//assert(myMesh);
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
		/*glGenBuffers(1, &myMesh->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, myMesh->VBO);
		glBindVertexArray(myMesh->VBO);*/
		//

		glBindVertexArray(myMesh->VAO);
		glDrawArrays(GL_TRIANGLES, 0, myMesh->data.size());
		//glGenBuffers(1, &VBO);
		glBindVertexArray(0);

		


		//myCube->DrawObject(myShader, this);

		/*glBindTexture(GL_TEXTURE_2D, 0);*/

	
	
}


