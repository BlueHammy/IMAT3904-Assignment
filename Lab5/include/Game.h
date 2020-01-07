#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"

class Scene;
class Model;

class Game
{
public:
	Game();
	IEngineCore* m_engineInterfacePtr;
	InputHandler* getInputHandler();
	InputHandler* m_inputHandler;

	std::vector<GameObject*> v_playerCubes;
	//Vector of game objects

	void update();
	void render();
	
	void loadLevel(std::string levelFile);

private:
	//Game objects, camera and background being added for later to be initialized, moved and drawn to the screen
	Camera m_camera;
	Scene* m_scene;
};
