#include "fstream"
#include "ObjLoader.h"
#include <iostream>
#include <sstream>
#include "Texture.h"
#include "VirtualObject.h"
using namespace std;

// do breakpoints

ObjLoader::ObjLoader()
{
	
}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool runOnce = false;
bool ObjLoader::ObjParser(std::string fileName, Mesh* INmesh)
{
	string message = "ObjLoaderStart";
	Message* mess = new Message(message);
	
	
	if (INmesh == nullptr)
	{
		return false;
	}

	Vertex vertex;
	Vertex vertexNor;
	Vertex vertexUV;
	Mesh& mesh = *INmesh;

	std::ifstream file(fileName);
	

	std::vector<Vertex> vertices;
	std::vector<Face> faces;

	
	
	std::string line;
	
	if (!file.is_open())
	{
		std::cerr <<  "Failed to open file: " << fileName << std::endl;
		return false;
	}

	while (std::getline(file, line)){
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		if (prefix == "v")
		{
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			
			temp_position.push_back(position);
			
		}
		if (prefix == "f")
		{
			Face face;
			int vertexIndex = 0;
			std::string newFace;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			if (newFace.length() >= 6 && runOnce == false) // This can't actually tell triangulated and non triangulated meshes apart.
			{
				runOnce = true;
				//std::cout << "This engine does not support mesh files with quads, please make sure the file is triangulated" << "\n";
				//std::exit(EXIT_FAILURE);
				//std::abort();
				
			}

			temp_faces.push_back(face);
			
		}
		if (prefix == "vt") 
		{
			glm::vec2 UV;
			iss >> UV.x >> UV.y;

			temp_uvs.push_back(UV);
		}

		if (prefix == "vn")
		{
			glm::vec3 NORMAL;
			iss >> NORMAL.x >> NORMAL.y >> NORMAL.z;

			temp_normals.push_back(NORMAL);
		}
		if (prefix == "mtllib") // load in the material from the file onto the mesh
		{
			
			/*char material[] = {255};
			iss >> material;
			std::cout << material , "\n";
			MeshTexture(material);*/

		}
		
	}

	

	file.close();
	

	for (int i = 0; i < temp_faces.size(); i++) 
	{
		Face face = temp_faces[i];
		for (int e = 0; e < 3; e++)
		{
			
			int index = face.positionIndices[e]; 
			
			
			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
				glm::vec3 position = temp_position[index - 1]; 

				mesh.data.push_back(position.x);
				mesh.data.push_back(position.y);
				mesh.data.push_back(position.z);
				
			}

			index = face.normalIndices[e];

			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
				glm::vec3 normal = temp_normals[index - 1];
				mesh.data.push_back(normal.x);
				mesh.data.push_back(normal.y);
				mesh.data.push_back(normal.z);
				

			}
			
			index = face.uvIndices[e];

			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
				glm::vec2 uv = temp_uvs[index - 1];
				mesh.data.push_back(uv.x);
				mesh.data.push_back(uv.y);
			}
			mesh.elements.push_back(mesh.numberVertices);
			mesh.numberVertices++;
			
		}
		
	}
	/*WriteToBinary(fileName, &file);
	ReadFromBinary(fileName, *file);*/
	return true;
}

inline std::vector<std::string> SplitString(const std::string& str, char delimeter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimeter))
	{
		tokens.push_back(token);
	
	}
	return tokens;

}

void ObjLoader::ParseFaceIndices(const std::string& string, Face& face, int vertexIndex)
{
	
	/*auto foundIndex = string.find('/');
	face_result = string.substr(0, foundIndex);*/

	char del = '/';

	std::string indexString = "";
	int indexCounter = 0;
	
	std::vector<std::string> tokens = SplitString(string, del);
	for (std::string& token : tokens)
	{
		int index = std::atoi(token.c_str());
		if (indexCounter == 0)
		{
			face.positionIndices[vertexIndex] = index;
		}
		else if (indexCounter == 2)
		{
			face.normalIndices[vertexIndex] = index;
		}
		else if (indexCounter == 1)
		{
			face.uvIndices[vertexIndex] = index;
		}
		indexCounter++;
	}
}

void ObjLoader::MeshTexture(char material[])
{
	//TextureOfMesh = new Texture(material);
}

std::ifstream in("./teapot.obj"); // in.txt out.bin | I don't know what else to do with serialisation
std::ofstream out("./out.bin", std::ios::binary); // does this create a file? Yes, It also changes files cause it can write in them


void ObjLoader::WriteToBinary() 
{
	size_t size;
	
	


	//std::ifstream file(FileName);

	/*file.open(FileName, std::ios::binary | std::ios::out);*/
	if (!out.is_open())
	{
		std::cerr << "There is no file for writing" << std::endl;

		//ofstream newFile("binaryFile.bin");

		//exit(1);
	}
	else
	{
		size = name.size();
		out.write((char*)&size, sizeof(size_t));
		out.write((char*)name.c_str(), size);
		size = type.size();
		out.write((char*)&size, sizeof(size_t));
		out.write((char*)type.c_str(), size);
	}


	

}

void ObjLoader::ReadFromBinary()
{
	size_t size = 0;
	char* data;
	//in.open("./teapot.obj");
	
	double d = 0;
	while (in >> d)
	{

		out.write((char*)&d, sizeof d);
	}

	if (!in.is_open())
	{
 		std::cerr << "There is no file for reading" << std::endl;

		
		
	}

	else
	{
		in.read((char*)&size, sizeof(size));
		data = new char[size + 1];
		in.read(data, size);
		data[size] = '\0';
		name = data;
		delete data;

		in.read((char*)&size, sizeof(size));
		data = new char[size + 1];
		in.read(data, size);
		data[size] = '\0';
		type = data;
		delete data;
	}
	
	

	


}



void Mesh::InitialiseMesh()
{
	//std::cout << "initialise object file" << "\n";
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	this->vertexbuffer = VBO;

	glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(float), &this->data[0], GL_STATIC_DRAW); // Data here is zero, for some reason

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(unsigned int), &this->elements[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	glBindVertexArray(0);
}
