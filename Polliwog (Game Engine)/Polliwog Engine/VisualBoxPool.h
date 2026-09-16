#pragma once

#ifndef _VisualBoxPool
#define _VisualBoxPool

#include <stack>

class BoxCmd;
class VisualizeCommand;

class VisualBoxPool
{
private:
	std::stack<BoxCmd*> recycledItems;

public:
	VisualBoxPool() = default;
	VisualBoxPool(const VisualBoxPool&) = delete;
	VisualBoxPool& operator=(const VisualBoxPool&) = delete;
	~VisualBoxPool();

	BoxCmd* GetVisual();

	void ReturnVisual(VisualizeCommand* b);
};

#endif _VisualBoxPool