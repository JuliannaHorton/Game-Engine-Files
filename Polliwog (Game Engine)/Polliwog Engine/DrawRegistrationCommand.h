#pragma once

#ifndef _DrawRegistrationCmd
#define _DrawRegistrationCmd

#include "SceneCommand.h"
class Drawable;

class DrawRegistrationCmd : public SceneCommand
{
public:

	DrawRegistrationCmd() = default;
	DrawRegistrationCmd(const DrawRegistrationCmd&) = delete;
	DrawRegistrationCmd& operator=(const DrawRegistrationCmd&) = delete;
	~DrawRegistrationCmd() = default; //This might be bad

	DrawRegistrationCmd(Drawable* Draw) : ptrDraw(Draw) {};

	virtual void execute();

private:

	Drawable* ptrDraw;
};


#endif _DrawRegistrationCmd