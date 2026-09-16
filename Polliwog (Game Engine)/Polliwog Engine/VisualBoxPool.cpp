#include "VisualBoxPool.h"
#include "BoxCmd.h"

VisualBoxPool::~VisualBoxPool()
{
	int sizecheck = recycledItems.size();
	sizecheck = 0;

	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}


}

BoxCmd* VisualBoxPool::GetVisual()
{
	BoxCmd* b;

	if (recycledItems.empty())
	{

		b = new BoxCmd();
	}
	else
	{
		b = recycledItems.top(); //Hmm, converting stuff like this might become a problem as I add more commands
		recycledItems.pop();

	}

	return b;
}

void VisualBoxPool::ReturnVisual(VisualizeCommand* b)
{
	recycledItems.push((BoxCmd*)(b));
}