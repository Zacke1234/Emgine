#pragma once

#include <string>
#include "vector"
#include "Message.h"
#include <map>

class MeshManager
{

public:
	MeshManager();
	~MeshManager();
	static void Allocate();
	static MeshManager& Get(); // Gets the singleton
//private:
	static MeshManager* instance; 
	
	

	//static void LoadMesh(char* fromPath);

	std::string msg;
	//Message* message = new Message(msg);


	ObjLoader* myObjLoader = new ObjLoader();
	
	Cube* LoadCube();
	Mesh* LoadMesh(std::string fromPath);
	Cube* cube;
	std::map<std::string, Mesh*> MeshCache;
	
	
};


