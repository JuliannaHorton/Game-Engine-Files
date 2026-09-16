#pragma once

#ifndef _VisualAABBPool
#define _VisualAABBPool

#include <stack>

class AABBCmd;
class VisualizeCommand;

class VisualAABBPool
{
private:
	std::stack<AABBCmd*> recycledItems;

public:
	VisualAABBPool() = default;
	VisualAABBPool(const VisualAABBPool&) = delete;
	VisualAABBPool& operator=(const VisualAABBPool&) = delete;
	~VisualAABBPool();

	AABBCmd* GetVisual();

	void ReturnVisual(VisualizeCommand* b);
};

#endif _VisualAABBPool