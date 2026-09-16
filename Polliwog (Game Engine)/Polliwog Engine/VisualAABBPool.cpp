#include "VisualAABBPool.h"
#include "AABBCmd.h"

VisualAABBPool::~VisualAABBPool()
{
	int sizecheck = recycledItems.size();
	sizecheck = 0;

	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}


}

AABBCmd* VisualAABBPool::GetVisual()
{
	AABBCmd* b;

	if (recycledItems.empty())
	{

		b = new AABBCmd();
	}
	else
	{
		b = recycledItems.top(); //Hmm, converting stuff like this might become a problem as I add more commands
		recycledItems.pop();

	}

	return b;
}

void VisualAABBPool::ReturnVisual(VisualizeCommand* b)
{
	recycledItems.push((AABBCmd*)(b));
}