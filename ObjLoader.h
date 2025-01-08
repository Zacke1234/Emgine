#include "vector"
#include <gtc/matrix_transform.hpp>
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <list>
#include <vec3.hpp>


#pragma once
struct Face {
	std::vector<int> vertexIndices;
	//float x, y, z;
};
struct Vertex {
	glm::vec3 position;
	//float x, y, z; //alt. 2
};
struct Mesh{
	/*Vertex vertices;
	glm::vec3 faces;*/
	
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	std::vector<float> data;
	int vertexbuffer;
};

// glm::vec3 


class ObjLoader
{
public:
	ObjLoader();
	Mesh ObjParser(const char* fileName);

	//
	
	std::vector <Vertex> tmp;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	//std::vector <glm::vec3> temp_vertices; // glm::vec3 
	std::vector<Vertex> temp_vertices; // glm::vec3
	std::vector<Vertex> temp_uvs;
	std::vector<Vertex> temp_normals;
	std::vector<Face> temp_faces;
};

