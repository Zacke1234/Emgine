#pragma once
#include "list"
#include "Cube.h"
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

	Cube* GetCube();
	Cube* GetObject();
	Cube* LoadCube();
	std::list<Cube*>* cubeList;
	Cube* cube;
	Cube* ObjectMesh;
	VirtualObject* virtobj;
};

