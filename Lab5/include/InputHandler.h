#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"

class GameObject;
class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& playerBackground) = 0;
};

class InputHandler
{
private:

	GameObject* m_playerCube;
	std::map<int, InputCommand*> m_controlMapping;

public:

	InputHandler(GameObject* playerCube);	// : m_playerCube(playerCube);
	void handleInputs(const std::vector<bool>& keyBuffer);
};


/*struct InputHandler
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
*/