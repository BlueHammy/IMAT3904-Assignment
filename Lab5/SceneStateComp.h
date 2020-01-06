#pragma once
#include "Component.h"

class SceneStateComp : public Component
{
public:
	SceneStateComp();
	~SceneStateComp();

	void OnUpdate(float dt) override;
	void OnMessage(const std::string msg) override;

	int GetSceneIndex();
	void SetSceneIndex(int newSceneIndex);

private:

	int m_sceneIndex;

};