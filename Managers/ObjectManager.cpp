#include "ObjectManager.h"

Object* ObjectManager::Create(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL) 
{
	Object* obj = new Object(_namn, Mesh, aTexture, aShader, aCollider);
	Object::Entities.push_back(obj);
	return obj;
}

void ObjectManager::Destroy(Object* obj) {
	Destroy(obj);
}

Object* ObjectManager::CreateLight(std::string aName = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* lightData = NULL)
{
	Object* lightObj = new Object(aName, Mesh, aTexture, aShader, aCollider);
	lightObj->SetLightData(lightData);
	Object::Entities.push_back(lightObj);
	return lightObj;
}
