#pragma once
#include "ObjLoader.h"
#include <string>
#include "vector"
#include <Message.h>
#include <map>
#include "Cube.h"
class ObjLoader;
class Cube;

class MeshManager // observer? subject? message to objloader? 
{
	
	ObjLoader* objLoader = nullptr;
public:
	MeshManager();
	~MeshManager();
	static void Allocate();
	static MeshManager& Get(); // Gets the singleton
//private:
	static MeshManager* instance; 
	
	
	//ConcreteMessage* message = new ConcreteMessage(c1,c2);
	//static void LoadMesh(char* fromPath);

	std::string msg;
	//Message* message = new Message(msg);


	
	
	Cube* LoadCube();
	Mesh* LoadMesh(std::string fromPath);
	Cube* cube;
	std::map<std::string, Mesh*> MeshCache;
	
	
};


