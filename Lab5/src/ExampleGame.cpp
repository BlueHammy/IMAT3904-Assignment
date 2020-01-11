#include "ExampleGame.h"

#include "ModelManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneStateComp.h"
#include <string>
#include <sstream>


ExampleGame::ExampleGame(IEngineCore* engine) : Game(engine)
{
	Initialise();
}

void ExampleGame::update(float dt)
{
	int desiredSceneIndex = m_scene->getPlayer()->getComponent<SceneStateComp>()->GetSceneIndex();

	if (desiredSceneIndex != m_sceneIndex)
	{
		delete m_scene;

		m_sceneIndex = desiredSceneIndex;

		m_scene = new Scene(m_levelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
		m_inputHandler = new InputHandler(m_scene->getPlayer()); 
	}
}
void ExampleGame::render()
{
	m_scene->render(m_engineInterfacePtr);

	double frameDuration = m_engineInterfacePtr->getFrameDuration();

	if (frameDuration > 0)
	{
		glm::vec3 eulerAngles = m_scene->getPlayer()->getEulerAngles();

		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		std::ostringstream oss;
		oss << " (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")"; 
																							   
		m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.01f, 1, glm::vec3(1, 1, 0));
	}
}

void ExampleGame::Initialise()
{
	m_theModelManager = new ModelManager();	
	m_scene = new Scene(m_levelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
	m_inputHandler = new InputHandler(m_scene->getPlayer());
}

