#pragma once

#ifndef _UpdateDeregistrationCmd
#define _UpdateDeregistrationCmd

#include "SceneCommand.h"
class Updatable;

class UpdateDeregistrationCmd : public SceneCommand
{
public:

	UpdateDeregistrationCmd() = default;
	UpdateDeregistrationCmd(const UpdateDeregistrationCmd&) = delete;
	UpdateDeregistrationCmd& operator=(const UpdateDeregistrationCmd&) = delete;
	~UpdateDeregistrationCmd() = default; //This might be bad

	UpdateDeregistrationCmd(Updatable* Up) : ptrUp(Up) {};

	virtual void execute();

private:

	Updatable* ptrUp;
};


#endif _UpdateDeregistrationCmd