#pragma once
//#include "Cube.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "ObjLoader.h"

#include "Lighting.h"
#include <vector>
#include "Collider.h"

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
class VirtualObject
{
public:
	VirtualObject();
	VirtualObject(Mesh* Mesh, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll/*, Lighting* light*/); // add lighting I suppose
	VirtualObject(Cube* Cube, Texture* aTexture, Shader* aShader, std::string _namn, Collider* coll/*, Lighting* light*/);
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
	Collider* myCollider;
	//Lighting* myLight;
	//std::shared_ptr<Mesh> aMesh = std::make_shared<Mesh>();
	
	//ObjLoader* myObjloader;
	


};

