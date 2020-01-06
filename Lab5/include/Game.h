#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"

class Game
{
public:
	Game();
	IEngineCore* m_engineInterfacePtr;

	InputHandler* m_inputHandler;

	std::vector<GameObject*> v_playerCubes;
	//Vector of game objects

	void update();
	void render();
	
	void loadLevel(std::string levelFile);

private:
	//Game objects, camera and background being added for later to be initialized, moved and drawn to the screen
	GameObject m_playerBackground;
	GameObject m_playerCube;
	GameObject m_playerCube1;
	GameObject m_playerCube2;
	Camera m_camera;
};
