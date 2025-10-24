#pragma once
#include "MeshLoader.h"
#include <string>
#include "vector"
#include <Message.h>
#include <map>
#include "Cube.h"
class MeshLoader;
class Cube;

class MeshManager // observer? subject? message to objloader? 
{
	
	MeshLoader* meshLoader = nullptr;
public:
	//Constructor and Destructor
	MeshManager();
	~MeshManager();

	// Message System Components
	//ConcreteMessage* message = new ConcreteMessage(c1,c2);
	//Message* message = new Message(msg);
	std::string msg;

	// Mesh Management
	std::map<std::string, Mesh*> MeshCache;
	Mesh* LoadMesh(std::string fromPath);
	Mesh* Create(std::string name = "newmesh", std::string path_end = NULL);
	
};


