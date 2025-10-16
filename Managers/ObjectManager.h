#pragma once
#include <vector>
#include <Object.h>
class ObjectManager
{
public:
	std::vector<Object*> objects;
	Object* Create(std::string aName, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* aCollider);
	void Destroy(Object* obj);


};

