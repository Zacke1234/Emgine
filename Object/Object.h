#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Shader\Lighting.h"
#include "Collider.h"
#include <vector>
#include <iostream>
#include "MeshManager.h"
#include <Cube.h>


inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		__debugbreak();
	}
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

class Cube;
struct Mesh;
struct LightData;

enum ObjectType
{
	Type_Light,
	Type_Mesh,
	Type_Cube
};



class Object
{
public:
	enum ObjectType type;
	
	
	Object(std::string _namn, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* coll);
	

	// should a virtual object contain a IsKinematic bool?
	void SetCube(Cube& aCube); 
	//void CreateCube(Cube& aCube); 
	void SetMesh(Mesh& mesh);
	void SetTexture(Texture& aTexture);
	void SetShader(Shader& aShader);
	void SetCollider(Collider& collider);
	
	//void SetLighting(Lighting& lighting);
	Mesh* CreateMesh();
	
	
	
	void Draw(Camera* aCamera, Shader* myShader);
	void DrawCube(Camera* aCamera, Shader* myShader);
	void DrawObject(Camera* aCamera, Shader* myShader);
	void UpdateTransform();

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;


	
	std::string namn;

	void SetName(std::string name);

	static std::vector<Object*> Entities;

	static int SelectedEntity;

	
	bool IsTransformValid;
	
	//std::mutex mtx; can't do mutex in header files
	//std::thread T1(); can't do thread in header files either
	glm::mat4 trans;
	Collider* myCollider;
	SphereCollider* mySphereColl;
	CubeCollider* myCubeColl;
	Mesh* myMesh;
	
	
	
private: 
	
	Texture* myTexture;
	Shader* MyShader;
	Cube* myCube;
	
	
	//Lighting* lighting;
	
	//ObjLoader* myObjLoader;
	
	//Lighting* myLight;
	//std::shared_ptr<Mesh> aMesh = std::make_shared<Mesh>();
	
	//ObjLoader* myObjloader;
	


};

class LightObject : public Object
{
public:
	LightObject(std::string _namn, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* coll, LightData* myLightData);
	static std::vector<LightObject*> LightEntities;
	LightData* myLightData;

	void SetLightData(LightData& lightdata);
	
};