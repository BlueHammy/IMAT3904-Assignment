#include "Model.h"
#include <assimp/postprocess.h>
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

Model::Model(string filepath)
{
	loadModel(filepath);
}


void Model::loadModel(string filepath)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	directory = filepath.substr(0, filepath.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}




void Model::processNode(aiNode* node, const aiScene* scene)
{
	
	for (int i = 0; i < static_cast<int>(node->mNumMeshes); i++)
	{
		int sceneMeshIndex = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[sceneMeshIndex];
		v_meshes.push_back(processMesh(mesh, scene));
	}
	
	for (int i = 0; i < static_cast<int>(node->mNumChildren); i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	
	vertices.resize(mesh->mNumVertices);
	indices.resize(mesh->mNumFaces * 3); 

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{

		vertices[i].position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertices[i].normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0])
		{
			vertices[i].textureCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertices[i].textureCoords = glm::vec2(0.0f, 0.0f);
		}

	}

	
	for (int i = 0; i < static_cast<int>(mesh->mNumFaces); i++)
	{
		
		for (int j = 0; j < static_cast<int>(mesh->mFaces[i].mNumIndices); j++)
			indices[3 * i + j] = mesh->mFaces[i].mIndices[j];
	}

	
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");


		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	
	return Mesh(vertices, indices, textures);
}

void Model::render(const unsigned shaderProgram)
{
	for (auto mesh : v_meshes)
	{
		mesh.render(shaderProgram);
	}
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	vector<Texture> textures;
	for (int i = 0; i < static_cast<int>(mat->GetTextureCount(type)); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool b_loadedTexture = false;
		for (auto texture : v_textures)
		{
			if (std::strcmp(texture.filepath.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(texture);
				b_loadedTexture = true;
				break;
			}
		}
		if (!b_loadedTexture)
		{
			
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.filepath = str;
			textures.push_back(texture);
			v_textures.push_back(texture); 
		}
	}
	return textures;
}


unsigned int Model::TextureFromFile(const char* filepath, const string& directory, bool gamma)
{
	string filename = string(filepath);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* textureData = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (textureData)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(textureData);
	}
	else
	{
		std::cout << "Texture failed to load from: " << filepath << std::endl;
		stbi_image_free(textureData);
	}

	return textureID;
}