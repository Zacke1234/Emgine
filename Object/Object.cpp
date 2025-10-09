#include <Object.h>
#include "Shader.h"
#include "Cube.h"
#include "ObjLoader.h"
#include "MeshManager.h"
#include "Physics.h"
#include <cassert>
#include <glad.h>
#include <thread>
#include "Collider.h"
#include <mutex>

std::mutex mtx;

using namespace std;

vector<Object*> Object::Entities;
int Object::SelectedEntity;



//auto object = new Object(mesh, myTexture, myShader);
Object::Object() // unitilized
{
	glm::vec3 center = { 0, 0,0 }; float radius = 10; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };
	glm::vec3 extents = { 1,1,1 };

	myCube = nullptr;
	myTexture = nullptr;
	MyShader = nullptr;
	myMesh = nullptr;
	myCollider = nullptr;
	trans = Math::identity4;
	IsTransformValid = false;
	//mySphereColl = nullptr;


	
	/*o->myCubeColl = new CubeCollider(center, extents, pos);
	o->mySphereColl = new SphereCollider(center, radius, pos);*/
	//myLight = nullptr;
	//isCube = false;

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	//Name[255] = nullptr;
}

Object::Object(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll) : Object()
{
	myTexture = aTexture;
	MyShader = aShader;
	myMesh = Mesh;
	
	this->namn = _namn;
	IsMesh = true;

	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);

	myCollider = coll;

	coll->position = this->Position;
	
	coll->isKinematic = false;
	coll->scale = Scale;
	//coll->mySphereColl;
	
	

}

Object::Object(Cube* cube, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll) : Object()
{
	myTexture = aTexture;
	MyShader = aShader;
	myCube = cube;
	
	this->namn = _namn;
	IsCube = true;

	myCollider = coll;
	
	
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);

	coll->position = this->Position;
	
	coll->isKinematic = false;
	coll->scale = Scale;

}


void Object::SetCube(Cube& aCube)
{
	myCube = &aCube;
	IsMesh = false;
	IsCube = true;
}

void Object::SetMesh(Mesh& mesh)
{
	myMesh = &mesh;
	IsMesh = true;
	IsCube = false;
}

void Object::SetTexture(Texture& aTexture)
{
	myTexture = &aTexture;
}

void Object::SetShader(Shader& aShader)
{
	MyShader = &aShader;
}

void Object::SetCollider(Collider& aCollider)
{
	myCollider = &aCollider;
}

Mesh* Object::CreateMesh() 
{
	
	myMesh = new Mesh();
	
	return myMesh;
}

void Object::SetName(std::string name)
{
	namn = name;
}

void Object::Draw(Camera* aCamera, Shader* myShader)
{
	
	if (IsCube)
	{
		//std::thread T1(DrawCube(aCamera, myShader));
		DrawCube(aCamera, myShader);
	}
	else if(IsMesh)
	{
		
		DrawObject(aCamera, myShader);
	}
}

void Object::DrawCube(Camera* aCamera, Shader* myShader)
{
	//thread T2(&Draw, this, aCamera);
	myCube->Draw(myShader, this, aCamera);
}

void Object::UpdateTransform()
{
	//mtx.lock();
	trans = Math::identity4;

	trans = glm::translate(trans, Position);

	trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

	trans = glm::scale(trans, Scale);

	IsTransformValid = true; 
	//mtx.unlock();
}

void Object::DrawObject(Camera* aCamera, Shader* myShader)
{
		
		
		//std::cout << "draw object in Object" << "\n";
		if (IsTransformValid == false)
		{
			/*thread T1(&Object::UpdateTransform);
			T1.join();*/
			UpdateTransform();

		}
		

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
		GL_CHECK(glDrawElements(GL_TRIANGLES, myMesh->elements.size(), GL_UNSIGNED_INT, (void*)0));
		
		GL_CHECK(glBindVertexArray(0));

		IsTransformValid = false;
}


