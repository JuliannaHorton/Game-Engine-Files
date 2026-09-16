#pragma once

#ifndef _VisualBSpherePool
#define _VisualBSpherePool

#include <stack>

class BSphereCmd;
class VisualizeCommand;

class VisualBSpherePool
{
private:
	std::stack<BSphereCmd*> recycledItems;

public:
	VisualBSpherePool() = default;
	VisualBSpherePool(const VisualBSpherePool&) = delete;
	VisualBSpherePool& operator=(const VisualBSpherePool&) = delete;
	~VisualBSpherePool();

	BSphereCmd* GetVisual();

	void ReturnVisual(VisualizeCommand* b);
};

#endif _VisualBSpherePool