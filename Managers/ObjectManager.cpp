#include "ObjectManager.h"

Object* ObjectManager::Create(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL)
{
	Object* obj = new Object(_namn, Mesh, aTexture, aShader, aCollider);
	Object::Entities.push_back(obj);
	return obj;
}

void ObjectManager::Destroy(Object* obj)
{
	
}
