#include "InputCommand.h"
#include "GameObject.h"

void RotateLeftCommand::execute(GameObject & cube)
{
	cube.OnMessage("rotateLeft");
}
