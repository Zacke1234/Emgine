#pragma once
#include "vector"
#include <gtc/matrix_transform.hpp>
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <list>
#include <vec3.hpp>


#pragma once
struct Face {
	
	int positionIndices[3] = {-1, -1, -1};
	int uvIndices[3] = { -1, -1, -1 };
	int normalIndices[3] = { -1, -1, -1 };
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0, 0, 1);
	glm::vec2 uv;
	
};

struct Mesh{
	
	
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	std::vector<float> data;
	std::vector<unsigned int> elements;
	int vertexbuffer = 0;
	unsigned int numberVertices = 0;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	size_t indexCount, vertexCount;

public:	
	void InitialiseMesh(Mesh* myMesh);
};


class ObjLoader
{
public:
	ObjLoader();
	Mesh ObjParser(std::string fileName);
	void ParseFaceIndices(const std::string& string, Face& face, int vertexIndex);
	void MeshTexture(char material[]);
	//
	
	std::vector <Vertex> tmp;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	//std::vector <glm::vec3> temp_vertices; // glm::vec3 
	std::vector<Vertex> temp_vertices; // glm::vec3
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Face> temp_faces;
	std::vector<glm::vec3> temp_position;
	std::string face_result;
};

