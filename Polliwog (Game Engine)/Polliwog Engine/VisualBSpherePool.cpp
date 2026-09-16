#include "VisualBSpherePool.h"
#include "BSphereCmd.h"

VisualBSpherePool::~VisualBSpherePool()
{
	int sizecheck = recycledItems.size();
	sizecheck = 0;

	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}


}

BSphereCmd* VisualBSpherePool::GetVisual()
{
	BSphereCmd* b;

	if (recycledItems.empty())
	{

		b = new BSphereCmd();
	}
	else
	{
		b = recycledItems.top(); //Hmm, converting stuff like this might become a problem as I add more commands
		recycledItems.pop();

	}

	return b;
}

void VisualBSpherePool::ReturnVisual(VisualizeCommand* b)
{
	recycledItems.push((BSphereCmd*)(b));
}