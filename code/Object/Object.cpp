#include <Object.h>
#include "Physics.h"
#include <cassert>
#include <glad.h>
#include <thread>
#include <mutex>
#include "Texture.h" 

std::mutex mtx;

using namespace std;

vector<Object*> Object::Entities;
int Object::SelectedEntity;





Object::Object(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL)
{
		// Name
	if (_namn != "new_object")
	{
		this->namn = _namn;
	}

		//Components
	if (Mesh)
	{
		SetMesh(*Mesh);
	}
	else {
		std::cout << "No mesh assigned to object: " << namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);
	}
	else {
		std::cout << "No texture assigned to object: " << namn << "\n";
	}
	if (aShader)
	{
		SetShader(*aShader);
	}
	else {
		std::cout << "No shader assigned to object: " << namn << "\n";
	}
	if (aCollider)
	{
		SetCollider(*aCollider);
	}
	else {
		std::cout << "No collider assigned to object: " << namn << "\n";
	}
}



void Object::SetCube(Cube& aCube)
{
	type = ObjectType::Type_Cube;
	myCube = &aCube;
}

void Object::SetMesh(Mesh& mesh)
{
	myMesh = &mesh;
	type = ObjectType::Type_Mesh;
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
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
	myCollider->position = this->Position;
	myCollider->isKinematic = false;
	myCollider->scale = Scale;
}
void Object::SetLightData(LightData* lightdata)
{
	type = ObjectType::Type_Light;
	myLightData = lightdata;
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
	DrawObject(aCamera, myShader);
	
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


