#include "SceneRegister.h"

void SceneRegister::addCommand(SceneCommand* cmd)
{
	myCommands.push(cmd);
}

void SceneRegister::executeCommands()
{
	SceneCommand* c;

	while (!myCommands.empty())
	{
		c = myCommands.front();
		c->execute();

		myCommands.pop();
	}
}