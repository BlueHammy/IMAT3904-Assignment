#pragma once

#include "GameObject.h"

class BackgroundColour : public GameObject
{
public:
	
	BackgroundColour();
	void OnUpdate(float dt) override;
	void OnMessage(const std::string msg) override;

};
