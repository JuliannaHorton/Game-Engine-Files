#pragma once

#ifndef _SceneCommand
#define _SceneCommand

class SceneCommand
{
public:
	SceneCommand() = default;
	SceneCommand(const SceneCommand&) = delete;
	SceneCommand& operator=(const SceneCommand&) = delete;
	virtual ~SceneCommand() = default;

	virtual void execute() = 0;
};


#endif _SceneCommand