#pragma once
#include "GameObject.h"

class Input : public GameObject
{
public:
	// has no model or transform
	Input();
	void OnUpdate(float dt);
	void OnMessage(const std::string msg);

};
