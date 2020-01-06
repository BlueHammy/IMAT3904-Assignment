#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"


class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& playerBackground) = 0;
};


struct InputHandler
{
	GameObject* m_playerCube;

	std::map<int, InputCommand*> m_controlMapping;

	InputHandler(GameObject* playerCube) : m_playerCube(playerCube)
	{
	
		//m_controlMapping[A] = new RotateLeftCommand();
		//Add Input Commands here for the first cube. Add Seperate InputHandlers for seperate gameObjects
	}

	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for (const auto& mapEntry : m_controlMapping)
		{
			if (keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(*m_playerCube);
			}
		}

	}
};
