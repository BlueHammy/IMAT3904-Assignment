#pragma once

#include <string>
#include <unordered_map>

class Model;

class ModelManager
{
public:

	ModelManager()
	{

	}
	~ModelManager()
	{

	}

	Model* getModel(std::string filename);


private:

	std::unordered_map<std::string, Model*> m_models;


};