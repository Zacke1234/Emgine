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
vector<Object*> SelectedEntityVec;
int LightObject::SelectedLightEntity;
vector<LightObject*> LightObject::LightEntities;
// Objects should hold all my meshes and lights
// Meshes should hold meshses like teapots, fishes and cubes
// Lighting should have lights, like directional, pointlight and spotlight etc (is that lightdata?)



Object::Object(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL)
{
	ObjType = Type_Mesh;
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
		std::cout << "No mesh assigned to object: " << _namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);
	}
	else {
		std::cout << "No texture assigned to object: " << _namn << "\n";
	}
	if (aShader)
	{
		SetShader(*aShader);
	}
	else {
		std::cout << "No shader assigned to object: " << _namn << "\n";
	}
	if (aCollider)
	{
		SetCollider(*aCollider);
	}
	else {
		std::cout << "No collider assigned to object: " << _namn << "\n";
	}
	/*if (*Objtype != Type_Mesh)
	{
		std::cout << "This is not a mesh " << _namn << "\n";
	}*/
	/*if (ObjectType::Type_Light)
	{
		myLightData = nullptr;
		
	}*/
	
}

LightObject::LightObject(std::string _namn = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL)
{
	ObjType = Type_Light;
	// Name
	if (_namn != "new_lightObject")
	{
		this->namn = _namn;
	}

	//Components
	if (Mesh)
	{

		SetMesh(*Mesh);
	}
	else {
		std::cout << "No mesh assigned to light object: " << _namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);
	}
	else {
		std::cout << "No texture assigned to light object: " << _namn << "\n";
	}
	if (aShader)
	{
		SetShader(*aShader);
	}
	else {
		std::cout << "No shader assigned to light object: " << _namn << "\n";
	}
	if (aCollider)
	{
		SetCollider(*aCollider);
	}
	else {
		std::cout << "No collider assigned to light object: " << _namn << "\n";
	}
	if (aLightData)
	{
		SetLightData(*aLightData);
	}
	else
	{
		std::cout << "No light data assigned to light object: " << _namn << "\n";
	}
	
}

void Object::SetCube(Cube& aCube)
{
	
	myCube = &aCube;
}

void Object::SetMesh(Mesh& mesh)
{
	myMesh = &mesh;
	
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
void LightObject::SetLightData(LightData& lightdata)
{
	
	myLightData = &lightdata;
	myLightData->lightPos = this->Position;
	
}
void LightObject::SetDirectional(LightData* aLightData)
{
	aLightData->LightVar = aLightData->DirLight;
}

void LightObject::SetPoint(LightData* aLightData)
{
	aLightData->LightVar = aLightData->PointLight;
}

void LightObject::SetSpot(LightData* aLightData)
{
	aLightData->LightVar = aLightData->SpotLight;
}

//void Object::SetLighting(Lighting& myLighting)
//{
//	type = ObjectType::Type_Light;
//	//lighting = &myLighting;
//}

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


