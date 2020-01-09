#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <fstream>
#include <sstream>

Game::Game(IEngineCore* engine) : m_engineInterfacePtr(engine)
{
}
Game::~Game()
{
}

InputHandler* Game::getInputHandler()
{
	return m_inputHandler;
}

//void Game::update()
//{
		
//	void loadLevel(std::string levelFile);
	
//}
