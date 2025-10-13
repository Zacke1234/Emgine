#pragma once
// observer pattern
#include <string>
#include <list>
#include <iostream>
#include <vector>
// Mesh manager and objectloaders will both be subscribers to this publisher 
// for the message output that is needed 


 
class Observer
{
public:
	
	virtual void Update(std::string message_from_subject) = 0;
	virtual ~Observer() {};
};

class Subject{
public:
	std::vector<Observer*> observers;
	std::string message;
	virtual void Attach(Observer *observer) = 0;
	virtual void Detach(Observer *observer) = 0;
	//virtual void AttachMesh(MeshManager* meshManager) = 0;
	//virtual void AttachObjLoader(ObjLoader* objload) = 0;
	virtual void Notify() = 0;

	~Subject() {};

}; 


