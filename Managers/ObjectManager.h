#pragma once
#include <vector>
#include <Object.h>
class ObjectManager : public Subject
{
public:
	std::vector<Object*> objects;

	std::vector<LightObject> lightsObjects;

	virtual Object* Create(std::string aName, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* aCollider) ;
	void Destroy(Object* obj);
	
	virtual LightObject* CreateLight(std::string aName, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* aCollider, LightData* lightData);

	void Attach(Observer* observer) override {
		observers.push_back(observer);

	}
	void Detach(Observer* observer) override {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void Notify() override {
		for (Observer* observer : observers)
		{
			observer->Update(message);
		}
	}

	
	
};

