#pragma once
class GameObject;

class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& cube) = 0;
};

class RotateLeftCommand : public InputCommand
{
	void execute(GameObject& cube);
};