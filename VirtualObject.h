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
	VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader);

	void SetCube(Cube& aCube); //would be SetMesh
	void SetTexture(Texture& aTexture);
	void SetShader(Shader& aShader);
	
	void Draw(Camera* aCamera, Shader* myShader);
	void DrawObject(Camera* aCamera, Shader* myShader);

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	char* name;

	static std::vector<VirtualObject*> Entities;

	static int SelectedEntity;

	
	
private:
	
	Texture* myTexture;
	Shader* MyShader;
	Cube* myCube;
	Mesh* myMesh;
	//ObjLoader* myObjloader;
	

	
};

