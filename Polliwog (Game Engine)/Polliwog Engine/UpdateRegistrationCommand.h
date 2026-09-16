#pragma once

#ifndef _UpdateRegistrationCmd
#define _UpdateRegistrationCmd

#include "SceneCommand.h"
class Updatable;

class UpdateRegistrationCmd : public SceneCommand
{
public:

	UpdateRegistrationCmd() = default;
	UpdateRegistrationCmd(const UpdateRegistrationCmd&) = delete;
	UpdateRegistrationCmd& operator=(const UpdateRegistrationCmd&) = delete;
	~UpdateRegistrationCmd() = default; //This might be bad

	UpdateRegistrationCmd(Updatable* Up) : ptrUp(Up) {};

	virtual void execute();

private:

	Updatable* ptrUp;
};


#endif _UpdateRegistrationCmd