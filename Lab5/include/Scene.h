#pragma once

#include "Model.h"

#include "GameObject.h"
#include "PlayerCharacter.h"
#include "IEngineCore.h"

#include <string>

class ModelManager;


class Scene
{

public:

	Scene(std::string filename, ModelManager* theModelManager, IEngineCore* engineCore);
	~Scene();


	void update(float dt);



	void render(IEngineCore* engineCore);



	void loadLevel(std::string levelFile);
	bool loadLevelJSON(std::string levelJSONFile);


	PlayerCharacter* getPlayer();

private:

	bool m_levelLoaded{ false };

	int m_playerIndex{ 1 };

	GameObject* m_playerBackground;


	std::vector<GameObject*> v_gameObjects;
	ModelManager* m_theModelManager;
	
	double m_oldMouseX;
	double m_oldMouseY;
	double m_mouseX;
	double m_mouseY;
	int m_mouseButtons;
	int m_oldMouseButtons;
	bool m_mouseEnabled{ false };
};
