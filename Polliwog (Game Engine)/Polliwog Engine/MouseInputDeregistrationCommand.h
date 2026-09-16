#pragma once

#ifndef _MouseInputDeregistrationCmd
#define _MouseInputDeregistrationCmd

#include "SceneCommand.h"
#include "EventType.h"
#include "../Mouse.h"

class Inputable;

class MouseInputDeregistrationCmd : public SceneCommand
{
public:

	MouseInputDeregistrationCmd() = default;
	MouseInputDeregistrationCmd(const MouseInputDeregistrationCmd&) = delete;
	MouseInputDeregistrationCmd& operator=(const MouseInputDeregistrationCmd&) = delete;
	~MouseInputDeregistrationCmd() = default; //This might be bad

	MouseInputDeregistrationCmd(Inputable* in) : ptrInput(in) {};

	void setKey(FROG_MOUSE k);
	void setEvent(EVENT_TYPE e);

	virtual void execute();

private:

	Inputable* ptrInput;
	FROG_MOUSE key;
	EVENT_TYPE event;
};


#endif _MouseInputDeregistrationCmd