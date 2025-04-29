#pragma once
#include "list"
#include "Cube.h"
#include "ObjLoader.h"
#include <string>

class MeshManager
{

public:
	MeshManager();
	static void Allocate();
	static MeshManager& Get(); // Gets the singleton
//private:
	static MeshManager* instance; 
	
	//static void LoadMesh(char* fromPath);

	ObjLoader* myObjLoader = new ObjLoader();
	
	Cube* LoadCube();
	Mesh* LoadMesh(std::string fromPath);
	std::vector<Cube*> cubeList;
	std::vector<Mesh*> meshList;
	
	
	std::unique_ptr<Mesh> Meshtest;
};
class cache
{

};

