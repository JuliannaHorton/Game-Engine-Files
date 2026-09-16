#pragma once

#ifndef _DrawDeregistrationCmd
#define _DrawDeregistrationCmd

#include "SceneCommand.h"
class Drawable;

class DrawDeregistrationCmd : public SceneCommand
{
public:

	DrawDeregistrationCmd() = default;
	DrawDeregistrationCmd(const DrawDeregistrationCmd&) = delete;
	DrawDeregistrationCmd& operator=(const DrawDeregistrationCmd&) = delete;
	~DrawDeregistrationCmd() = default; //This might be bad

	DrawDeregistrationCmd(Drawable* Draw) : ptrDraw(Draw) {};

	virtual void execute();

private:

	Drawable* ptrDraw;
};


#endif _DrawDeregistrationCmd