#include "Memory.h"
//#include <Psapi.h>
#include <Windows.h>
#include <crtdbg.h>
#include <iostream>
#include <tchar.h>

#define _CRTDBG_MAP_ALLOC
#define WIDTH 7

Memory::Memory()
{

}

bool Memory::HasMemoryAvailable(int megaBytes)
{

	//GetProcessMemoryInfo(megaBytes, );
	
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	//std::cout << status.ullTotalPhys + " megabytes \n" << endl;
	//std::cout << "There are %*ld percent of memory in use.\n", status.dwMemoryLoad;
	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, status.dwMemoryLoad); // % does not show up in the message
	return status.ullTotalPhys;
	
	
}

std::thread Memory::T1()
{
	return std::thread();
}

void Memory::ClearMemory(Shader* CmyShader, Cube* CmyCube, Camera* CmyCamera, Lighting* CmyLighting, VirtualObject* CvirtObj, UI* CmyUI, MeshManager* CmyMeshManager, Mesh* CObjLoader, Physics* CmyPhysics, Collider* CmyCollider)
{
	myShader = CmyShader;
	delete CmyShader;
	myCube = CmyCube;
	delete CmyCube;
	myCamera = CmyCamera;
	delete CmyCamera;
	myLighting = CmyLighting;
	delete CmyLighting;
	virtObj = CvirtObj;
	delete CvirtObj;
	myUI = CmyUI;
	delete CmyUI;
	myMeshManager = CmyMeshManager;
	delete CmyMeshManager;
	myMesh = CObjLoader;
	delete CObjLoader;
	myPhysics = CmyPhysics;
	delete CmyPhysics;
	myCollider = CmyCollider;
	delete CmyCollider;
	
}

void Memory::LoadInMemory(Shader* myShader, Cube* myCube, Camera* myCamera, Lighting* myLighting, VirtualObject* virtObj, UI* myUI, MeshManager* myMeshManager, Mesh* ObjLoader, Physics* myPhysics, Collider* myCollider)
{
	
}

