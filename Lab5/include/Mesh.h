#pragma once

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

struct Texture {
	unsigned int id;
	string type;
	aiString filepath;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void render(const unsigned int shaderProgram);

private:
	
	unsigned int VBO, EBO;

	void setupMesh();

};