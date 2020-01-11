#pragma once
#include "SceneStateComp.h"


SceneStateComp::SceneStateComp()
{
	m_sceneIndex = 0;
}
SceneStateComp::~SceneStateComp()
{

}

void SceneStateComp::OnUpdate(float dt)
{

}
void SceneStateComp::OnMessage(const std::string msg)
{
	if (msg == "Level1") //allowing the user to change levels if they have an input command to assign buttons to change the levels.
	{
		SetSceneIndex(0);
	}
	else if (msg == "Level2")
	{
		SetSceneIndex(1);
	}
}

int SceneStateComp::GetSceneIndex()
{
	return m_sceneIndex;
}
void SceneStateComp::SetSceneIndex(int newSceneIndex)
{
	m_sceneIndex = newSceneIndex;
}

