#pragma once

#ifndef _BSphereCmd
#define _BSphereCmd

#include "VisualizeCommand.h"
#include "../PollywogBog.h"


class BSphereCmd : public VisualizeCommand
{
public:

	BSphereCmd() = default;
	BSphereCmd(const BSphereCmd&) = delete;
	BSphereCmd& operator=(const BSphereCmd&) = delete;
	~BSphereCmd() = default;

	BSphereCmd(Matrix M, Vect col) : World(M), Color(col) {};

	void setVisual(Matrix M, Vect C) { World = M; Color = C; };

	virtual void execute();
	virtual void returnCmd();

private:
	Matrix World = Matrix(IDENTITY);
	Vect Color = Vect(0, 0, 0, 0);
};


#endif _BSphereCmd