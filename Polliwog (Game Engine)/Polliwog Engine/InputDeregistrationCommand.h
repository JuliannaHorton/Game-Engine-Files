#pragma once

#ifndef _InputDeregistrationCmd
#define _InputDeregistrationCmd

#include "SceneCommand.h"
#include "EventType.h"
#include "../Keyboard.h"


class Inputable;

class InputDeregistrationCmd : public SceneCommand
{
public:

	InputDeregistrationCmd() = default;
	InputDeregistrationCmd(const InputDeregistrationCmd&) = delete;
	InputDeregistrationCmd& operator=(const InputDeregistrationCmd&) = delete;
	~InputDeregistrationCmd() = default; //This might be bad

	InputDeregistrationCmd(Inputable* in) : ptrInput(in) {};

	void setKey(FROG_KEY k);
	void setEvent(EVENT_TYPE e);

	virtual void execute();

private:

	Inputable* ptrInput;
	FROG_KEY key;
	EVENT_TYPE event;
};


#endif _InputDeregistrationCmd