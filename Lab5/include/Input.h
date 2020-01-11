#pragma once

class GameObject;

class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& player) = 0;
};

class RotateLeftCommand : public InputCommand
{
	void execute(GameObject& player);
};

class RotateRightCommand : public InputCommand
{
	void execute(GameObject& player);
};

class RotateUpCommand : public InputCommand
{
	void execute(GameObject& player);
};

class RotateDownCommand : public InputCommand
{
	void execute(GameObject& player);
};

class MoveForwardCommand : public InputCommand
{
	void execute(GameObject& player);
};

class MoveBackCommand : public InputCommand
{
	void execute(GameObject& player);
};


class MoveUpCommand : public InputCommand
{
	void execute(GameObject& player);
};
class MoveDownCommand : public InputCommand
{
	void execute(GameObject& player);
};

class CameraFirstCommand : public InputCommand
{
	void execute(GameObject& player);
};
class CameraThirdCommand : public InputCommand
{
	void execute(GameObject& player);
};
class ResetCommand : public InputCommand
{
	void execute(GameObject& player);
};

class GotoLevel1Command : public InputCommand
{
	void execute(GameObject& player);
};

class GotoLevel2Command : public InputCommand
{
	void execute(GameObject& player);
};