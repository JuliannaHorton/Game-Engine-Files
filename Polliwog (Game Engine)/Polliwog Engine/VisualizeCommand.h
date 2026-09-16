#pragma once

#ifndef _VisualizeCommand
#define _VisualizeCommand

class VisualizeCommand
{
public:
	VisualizeCommand() = default;
	VisualizeCommand(const VisualizeCommand&) = delete;
	VisualizeCommand& operator=(const VisualizeCommand&) = delete;
	virtual ~VisualizeCommand() = default;

	virtual void execute() = 0;
	virtual void returnCmd() = 0;
};


#endif _VisualizeCommand