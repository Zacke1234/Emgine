#include "fstream"
#include "ObjLoader.h"
#include <iostream>
#include <sstream>

// do breakpoints

ObjLoader::ObjLoader()
{
	
}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/


Mesh ObjLoader::ObjParser(const char* fileName)
{
	
	Vertex vertex;
	Mesh mesh;
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	std::ifstream file(fileName);
	
	std::string line;
	if (!file.is_open())
	{
		std::cerr <<  "Failed to open file: " << fileName << std::endl;
		return mesh;
	}

	while (std::getline(file, line)){
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		if (prefix == "v")
		{
			
			iss >> vertex.position.x >> vertex.position.y >> vertex.position.z;
			//std::cout << temp_vertices[vertex.z][vertex.x] << " ";
			temp_vertices.push_back(vertex);
			// Severity	Code	Description	Project	File	Line	Suppression State	Details
			// Error	C2039	'push_back': is not a member of 'glm::vec<3,float,glm::packed_highp>'	Emgine	C : \Users\zackarias.hager\source\repos\Emgine\Emgine\ObjLoader.cpp	42
			// How do I include my glm::vec3 into my Vertex struct without errors?
		}
		if (prefix == "f")
		{
			Face face;
			//iss >> face.x >> face.y >> face.z;
			int newInt;
			iss >> newInt;
			face.vertexIndices.push_back(newInt);
			iss >> newInt;
			face.vertexIndices.push_back(newInt);
			iss >> newInt;
			face.vertexIndices.push_back(newInt);
			temp_faces.push_back(face);
			// f 3227 3239 3243
			// face
		}

		/*for (unsigned int i = 0; i < objl.vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = objl.vertexIndices[i];
			objl.out_vertices.push_back(vertex);
		}*/
	}

	//vertices = objl.out_vertices;
	//assert(file);
	file.close();
	
	

	for (int i = 0; i < temp_faces.size(); i++)
	{
		Face face = temp_faces[i];

		for (int e = 0; e < face.vertexIndices.size(); e++)
		{
			int index = face.vertexIndices[e];
			vertex = temp_vertices[index - 1];
			mesh.data.push_back(vertex.position.x);
			mesh.data.push_back(vertex.position.y);
			mesh.data.push_back(vertex.position.z);

			// all of these are important for the mesh, except for the position.g it seems like
			mesh.data.push_back(vertex.position.b);
			//mesh.data.push_back(vertex.position.g);
			mesh.data.push_back(vertex.position.p);
			mesh.data.push_back(vertex.position.r);
			mesh.data.push_back(vertex.position.s);
			mesh.data.push_back(vertex.position.t);
			mesh.numberVertices++;
			
		}
	}
	//return vertices;
	return mesh;
	//return std::vector<Vertex>();
}


