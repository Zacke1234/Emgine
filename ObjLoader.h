#pragma once
#include "vector"
#include "Message.h"
#include <gtc/matrix_transform.hpp>
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <list>
#include "fstream"
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
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	size_t indexCount = 0, vertexCount = 0;

public:	
	void InitialiseMesh();
};


class ObjLoader
{
public:
	
	ObjLoader();
	bool ObjParser(std::string fileName, Mesh* mesh);
	void ParseFaceIndices(const std::string& string, Face& face, int vertexIndex);
	void MeshTexture(char material[]);
	void WriteToBinary(std::ostream& f);
	void ReadFromBinary(std::istream& f);
	
	MessageQueueComponent1* c1 = new MessageQueueComponent1;
	MessageQueueComponent2* c2 = new MessageQueueComponent2;

	std::string name;
	std::string type;

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

class BinaryFile
{
private:
	std::string FileName;
	std::fstream File;
public:
	BinaryFile(std::string FileName) : FileName(FileName) {};
	void WriteFile();

	void ReadFile();
	
};

