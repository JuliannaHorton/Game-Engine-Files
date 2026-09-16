#pragma once

#ifndef _AABBCmd
#define _AABBCmd

#include "VisualizeCommand.h"
#include "../PollywogBog.h"


class AABBCmd : public VisualizeCommand
{
public:

	AABBCmd() = default;
	AABBCmd(const AABBCmd&) = delete;
	AABBCmd& operator=(const AABBCmd&) = delete;
	~AABBCmd() = default;

	AABBCmd(Matrix M, Vect col) : World(M), Color(col) {};

	void setVisual(Matrix M, Vect C) { World = M; Color = C; };

	virtual void execute();
	virtual void returnCmd();

private:
	Matrix World = Matrix(IDENTITY);
	Vect Color = Vect(0, 0, 0, 0);
};


#endif _AABBCmd