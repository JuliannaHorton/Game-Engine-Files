#include "TerrainRectangleArea.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "CollisionAABB.h"
#include "TRAIterator.h"

TerrainRectangleArea::TerrainRectangleArea(Collidable* Col)
{
	pTerrain = SceneManager::getTerrain();
	const CollisionBSphere& bs = Col->GetDefaultBSphere();

	CollisionAABB Box;
	Box.ComputeData(bs);

	//Grab the cells directly below 'testBox's min and max
	Vect minV = Box.GetMin();
	Vect maxV = Box.GetMax();

	// the cell pair, so std::pair<int, int>
	start = pTerrain->GetCellBelow(minV);
	end = pTerrain->GetCellBelow(maxV);
}

Cell TerrainRectangleArea::Next(int x, int y) //I called it next but it just allows access to the terrains cell
{
	return pTerrain->GetCell(x, y);
}

CollisionAABB* TerrainRectangleArea::getTerrBox() //Needed a pointer to a stored AABB, so I used the one I already had inside Terrain
{
	return pTerrain->returnBox();
}

TRAIterator TerrainRectangleArea::Begin()// Return First Cell
{
	return TRAIterator(start, this);
}

TRAIterator TerrainRectangleArea::End()
{
	return TRAIterator(end, this);
}