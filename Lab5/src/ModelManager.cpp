#include "ModelManager.h"

#include "Model.h"


Model* ModelManager::getModel(std::string filename)
{


	auto iter = m_models.find(filename);

	if (iter != std::end(m_models))
	{
		
		return iter->second;
	}
	else
	{
		
		Model* thisModel = new Model(filename);
		m_models[filename] = thisModel;


		return thisModel;
	}

}