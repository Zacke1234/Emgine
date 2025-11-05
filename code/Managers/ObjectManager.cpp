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

LightObject* ObjectManager::CreateLight(std::string aName = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL)
{
	LightObject* lightObj = new LightObject(aName, Mesh, aTexture, aShader, aCollider, aLightData);
	//lightObj->type = ObjectType::Type_Light;
	//lightObj->SetLightData(lightData);
	//lightObj->SetLighting(*lightData);
	Object::Entities.push_back(lightObj);
	LightObject::LightEntities.push_back(lightObj);
	return lightObj;
}

Object* ObjectManager::Find(std::string aName)
{
	for (Object* object : Object::Entities)
	{
		if (object->namn == aName)
		{
			std::cout << "Object found: " << aName << "\n";
			return object;
		}
	}
	std::cout << "Object not found: " << aName << "\n";
	return nullptr;
}

// Lightdata is part of Object Yes?
// So Do I have lightdata in object.h/cpp?
// and slash or?
// ponder on this

// Obviously I want a object to be able to hold a light, depending on whatever
// that light is 