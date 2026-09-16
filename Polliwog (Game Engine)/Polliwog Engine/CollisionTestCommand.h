#pragma once

#ifndef _CollisionTestCmd
#define _CollisionTestCmd

class CollisionTestCmd
{
public:
	CollisionTestCmd() = default;
	CollisionTestCmd(const CollisionTestCmd&) = delete;
	CollisionTestCmd& operator=(const CollisionTestCmd&) = delete;
	virtual ~CollisionTestCmd() = default;

	virtual void execute() = 0;
};

#endif _CollisionTestCmd