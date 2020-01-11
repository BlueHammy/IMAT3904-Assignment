#pragma once
#include <map>
#include <vector>
#include "Input.h"

class GameObject;

class InputHandler
{
private:

	GameObject* m_playerCube;
	std::map<int, InputCommand*> m_controlMapping;

public:

	InputHandler(GameObject* playerCube);
	void handleInputs(const std::vector<bool>& keyBuffer);
};
