#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <fstream>
#include <sstream>

Game::Game()
{
	m_engineInterfacePtr = nullptr;
	m_inputHandler = new InputHandler(&m_playerCube); //this would initilize the input commands, on this single game object (playerCube), if they were implemented

	m_playerBackground.addComponent(new RedComponent);
	m_playerBackground.addComponent(new GreenComponent);
	m_playerBackground.addComponent(new BlueComponent);

	//allows the game objects to be moved
	m_playerCube.addComponent(new TransformComponent);
	m_playerCube1.addComponent(new TransformComponent);
	m_playerCube2.addComponent(new TransformComponent);
	
	
	TransformComponent* temp = m_playerCube.getComponent<TransformComponent>();
	TransformComponent* temp1 = m_playerCube1.getComponent<TransformComponent>();
	TransformComponent* temp2 = m_playerCube2.getComponent<TransformComponent>();
	//move the objects to where ever you want on the screen
	temp->translate(0, 0, -5);
	temp1->translate(1, 1, -5);
	temp2->translate(-1, 1, -5);

	

}

void Game::update()
{
		
	void loadLevel(std::string levelFile);
	
}

void Game::render()
{
	float redValue = 112, greenValue = 0, blueValue = 55;
	if(m_playerBackground.getComponent<RedComponent>())
		redValue = m_playerBackground.getComponent<RedComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<GreenComponent>())
		greenValue = m_playerBackground.getComponent<GreenComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<BlueComponent>())
		blueValue = m_playerBackground.getComponent<BlueComponent>()->m_colourValue;

	
	
	
	m_engineInterfacePtr->renderColouredBackground(redValue, greenValue, blueValue);
	
	m_engineInterfacePtr->setCamera(&m_camera);

	//draw the cubes
	m_engineInterfacePtr->drawCube(m_playerCube.getComponent<TransformComponent>()->getModelMatrix());
	m_engineInterfacePtr->drawCube(m_playerCube1.getComponent<TransformComponent>()->getModelMatrix());
	m_engineInterfacePtr->drawCube(m_playerCube2.getComponent<TransformComponent>()->getModelMatrix());
	loadLevel("assets/levels/myCubeLevel.txt");
}

void Game::loadLevel(std::string levelFile)
{

	std::ifstream myInputFile;
	myInputFile.open(levelFile, std::ios_base::in);

	std::stringstream ss;
	std::string s;

	int numCubesToRead;
	//text file reading - for loading simple game levels
	if (myInputFile.is_open())
	{
		std::getline(myInputFile, s);
		ss.str(s);
		ss >> numCubesToRead;


		v_playerCubes.resize(numCubesToRead);
		ss.clear();

		for (int i = 0; i < numCubesToRead; i++)
		{
			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float x;
			float y;
			float z;

			ss >> x;
			ss >> y;
			ss >> z;
			glm::vec3 pos(x, y, z);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float ow;
			float ox;
			float oy;
			float oz;

			ss >> ow;
			ss >> ox;
			ss >> oy;
			ss >> oz;
			glm::quat orient(ow, ox, oy, oz);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float sx;
			float sy;
			float sz;

			ss >> sx;
			ss >> sy;
			ss >> sz;

			glm::vec3 scale(sx, sy, sz);
		}
	}
}