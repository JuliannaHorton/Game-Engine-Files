#pragma once

#ifndef _BoxCmd
#define _BoxCmd

#include "VisualizeCommand.h"
#include "../PollywogBog.h"


class BoxCmd : public VisualizeCommand
{
public:

	BoxCmd() = default;
	BoxCmd(const BoxCmd&) = delete;
	BoxCmd& operator=(const BoxCmd&) = delete;
	~BoxCmd() = default;

	BoxCmd(Matrix M, Vect col) : World(M), Color(col) {};

	void setVisual(Matrix M, Vect C) { World = M; Color = C; };

	virtual void execute();
	virtual void returnCmd();

private:
	Matrix World = Matrix(IDENTITY);
	Vect Color = Vect(0, 0, 0, 0);
};


#endif _AABBCmd