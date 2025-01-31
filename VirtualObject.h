#pragma once
//#include "Cube.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "ObjLoader.h"
#include <vector>

class Cube;
class VirtualObject
{
public:
	VirtualObject();
	VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn);
	VirtualObject(Cube* Cube, Texture* aTexture, Shader* aShader, std::string _namn);
	~VirtualObject();

	void SetCube(Cube& aCube); 
	void CreateCube(Cube& aCube); 
	void SetTexture(Texture& aTexture);
	void SetShader(Shader& aShader);
	void CreateMesh(Mesh& aMesh);
	void SetMesh(Mesh& aMesh);

	
	void Draw(Camera* aCamera, Shader* myShader);
	void DrawCube(Camera* aCamera, Shader* myShader);
	void DrawObject(Camera* aCamera, Shader* myShader);

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	
	std::string namn;

	void SetName(std::string name);

	static std::vector<VirtualObject*> Entities;

	static int SelectedEntity;

	bool IsCube;
	bool IsMesh;

	
	
private:
	
	Texture* myTexture;
	Shader* MyShader;
	Cube* myCube;
	Mesh* myMesh;
	ObjLoader* myObjLoader;
	//std::shared_ptr<Mesh> aMesh = std::make_shared<Mesh>();
	
	//ObjLoader* myObjloader;
	

	
};

