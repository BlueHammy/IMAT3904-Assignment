#pragma once

#include "BackgroundColour.h"
#include "Component.h"
#include "ColourComponent.h"

BackgroundColour::BackgroundColour()
{
	addComponent(new RedComponent());
	addComponent(new GreenComponent());
	addComponent(new BlueComponent());
}

void BackgroundColour::OnUpdate(float dt)
{
}
void BackgroundColour::OnMessage(const std::string msg)
{
}

