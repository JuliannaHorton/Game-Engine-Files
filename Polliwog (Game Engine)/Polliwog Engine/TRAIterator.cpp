#include "TRAIterator.h"
#include "TerrainRectangleArea.h"

TRAIterator::TRAIterator(std::pair<int, int> cel, TerrainRectangleArea* area)
	: current(cel), pArea(*area)
{
	itCell = pArea.Next(current.first, current.second);
}

TRAIterator& TRAIterator::operator++()
{
	// Increase row and/or col by one 
	// while staying within the bounds
	// of begin/end pairs

	// Grab End and Begin from Terrain Area
	const std::pair<int, int> endPair = pArea.End().current;
	const std::pair<int, int> beginPair = pArea.Begin().current;

	// Check if wheres its at on the row and col
	if (current.second == endPair.second) //Checks if col has finished
	{
		current.second = beginPair.second; // Reset column
		current.first++; // Move to next row
	}
	else
	{
		current.second++; //Move up a column
	}

	itCell = pArea.Next(current.first, current.second); //Grab next cell
	return *this;
}

bool TRAIterator::operator!=(const TRAIterator& other) const
{
	return current.first != other.current.first + 1; //Added a plus one to the column, so that the loop ends after the last cell
}

CollisionAABB* TRAIterator::getCellAABB()
{
	CollisionAABB* currBox = pArea.getTerrBox(); //Grab box from terrain
	currBox->ComputeData(itCell.Min, itCell.Max); //Compute AABB for Cell

	return currBox;
}