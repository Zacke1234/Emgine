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
	//myLight = nullptr;
	//isCube = false;

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	//Name[255] = nullptr;
}

VirtualObject::VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll/*, Lighting* light*/)
{
	//myCube = aCube;
	myTexture = aTexture;
	MyShader = aShader;
	myMesh = Mesh;
	//Name[255] = aName[255];
	this->namn = _namn;
	IsMesh = true;
	myCollider = coll;
	//myLight = light;
	

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);

}

VirtualObject::VirtualObject(Cube* cube, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll/*, Lighting* light*/)
{
	myTexture = aTexture;
	MyShader = aShader;
	myCube = cube;
	//Name[255] = aName[255];
	this->namn = _namn;
	IsCube = true;
	//myLight = light;

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

void VirtualObject::CreateMesh(Mesh& aMesh) // does nothing
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
		glm::mat4 trans = glm::mat4(1.0f);

		trans = glm::translate(trans, Position);

		trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
		trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
		trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

		trans = glm::scale(trans, Scale);


		MyShader->SetMatrix("transform", trans);
		MyShader->SetMatrix("view", aCamera->myView);
		MyShader->SetMatrix("projection", aCamera->projection);
		
		if (myTexture != NULL && myTexture->IsValid())
		{
			GL_CHECK(glActiveTexture(GL_TEXTURE0)); // Activate the texture unit before binding texture
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));
			GL_CHECK(glActiveTexture(GL_TEXTURE0));
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));

			GL_CHECK(glActiveTexture(GL_TEXTURE1));
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));
		}
		
		
		GL_CHECK(glBindVertexArray(myMesh->VAO));
		GL_CHECK(glDrawElements(GL_TRIANGLES, myMesh->elements.size(), GL_UNSIGNED_INT, 0));
		
		GL_CHECK(glBindVertexArray(0));
}


