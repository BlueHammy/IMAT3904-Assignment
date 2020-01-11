#include "InputHandler.h"
#include <map>
#include <vector>

InputHandler::InputHandler(GameObject* playerCube) : m_playerCube(playerCube)
{

	//Able to add, remove and adjust input commands to fit the needs of the game

	m_controlMapping[(int)'W'] = new MoveForwardCommand();
	m_controlMapping[(int)'A'] = new RotateLeftCommand();
	m_controlMapping[(int)'S'] = new MoveBackCommand();
	m_controlMapping[(int)'D'] = new RotateRightCommand();
	
	m_controlMapping[(int)'M'] = new MoveUpCommand();
	m_controlMapping[(int)'N'] = new MoveDownCommand();

	m_controlMapping[(int)'Q'] = new RotateUpCommand();
	m_controlMapping[(int)'E'] = new RotateDownCommand();

	m_controlMapping[32] = new ResetCommand();

	m_controlMapping[(int)'1'] = new CameraFirstCommand();
	m_controlMapping[(int)'2'] = new CameraThirdCommand();

	m_controlMapping[(int)'-'] = new GotoLevel1Command();
	m_controlMapping[(int)'='] = new GotoLevel2Command();

}

void InputHandler::handleInputs(const std::vector<bool>& keyBuffer)
{
	for (const auto& mapEntry : m_controlMapping)
	{
		if (keyBuffer[mapEntry.first])
		{
			mapEntry.second->execute(*m_playerCube);
		}
	}

}