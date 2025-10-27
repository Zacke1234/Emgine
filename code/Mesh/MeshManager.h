#pragma once
#include "MeshLoader.h"
#include <string>
#include "vector"
#include <Message.h>
#include <map>
#include "Cube.h"
class MeshLoader;
class Cube;

class MeshManager : public Observer
{
	
	MeshLoader* meshLoader = nullptr;
public:
	//Constructor and Destructor
	MeshManager();
	~MeshManager();



	void Update(std::string message_from_subject) override {
		std::cout << "MeshManager received message: " << message_from_subject << "\n";
	};

	std::string msg;

	// Mesh Management
	std::map<std::string, Mesh*> MeshCache;
	Mesh* LoadMesh(std::string fromPath);
	Mesh* Create(std::string name = "newmesh", std::string path_end = NULL);
	
};


