#include "PlayerCharacter.h"




// constructor
PlayerCharacter::PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	addComponent(tc);
	addComponent(new ModelComponent(model));
	addComponent(new CameraComponent());
	addComponent(new SceneStateComp());
	SetCameraPositionFromTransformComponent(tc);
}
PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::OnUpdate(float dt)
{
}
void PlayerCharacter::OnMessage(const std::string msg)
{

	TransformComponent* tc = getComponent<TransformComponent>();

	if (msg == "setCameraFirstPerson")
	{
		m_cameraState = CameraViewState::firstPersonCamera;
	}
	else if (msg == "setCameraThirdPerson")
	{
		m_cameraState = CameraViewState::thirdPersonCamera;
	}
	else if (msg == "Level1")
	{
	
		getComponent<SceneStateComp>()->OnMessage("Level1");
	}
	else if (msg == "Level2")
	{
		getComponent<SceneStateComp>()->OnMessage("Level2");

	}
	else
	{
		
		tc->OnMessage(msg);
	}
	SetCameraPositionFromTransformComponent(tc);
}

void PlayerCharacter::SetCameraPositionFromTransformComponent(TransformComponent* tc)
{
	
	glm::vec3 pos = tc->m_position;
	glm::quat orient = tc->getOrientation();
	

	glm::vec3 relativePosition;
	if (m_cameraState == CameraViewState::thirdPersonCamera)
	{
		relativePosition = glm::vec3(0, 1.5, 6);		
	}
	else
	{
		relativePosition = glm::vec3(0, 0.5, -0.95);	
	}
	pos += orient * relativePosition;

	
	CameraComponent* cc = getComponent<CameraComponent>();
	cc->setPosition(pos);
	cc->setOrientation(orient);
}

glm::vec3 PlayerCharacter::getEulerAngles()
{
	TransformComponent* tc = getComponent<TransformComponent>();

	return tc->getEulerAngles();
}

