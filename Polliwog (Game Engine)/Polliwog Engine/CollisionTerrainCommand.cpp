#include "CollisionTerrainCommand.h"
#include "CollisionDispatchBase.h"
#include "CollisionBSphere.h"
#include "CollisionVolume.h"
#include "CollidableGroup.h"
#include "MathTools.h"
#include "Visualizer.h"

#include "TRAIterator.h"
#include "TerrainRectangleArea.h"

void CollisionTerrainCmd::execute()
{
    const DifCollidableCollection& Collection = pG->GetColliderCollection();

    for (auto it = Collection.begin(); it != Collection.end(); it++) // every collidable in group
    {
        TerrainRectangleArea CandidateCells = TerrainRectangleArea(*it); // gets the min and max below

            for (TRAIterator itCell = CandidateCells.Begin(); itCell != CandidateCells.End(); ++itCell)
            {
                // Get AABB from the itCell iterator
                CollisionAABB* cellBox = itCell.getCellAABB();

				if (MathTools::Intersect(*cellBox, (*it)->GetDefaultBSphere()))
				{
					//Test for user-volume 
					Visualizer::ShowCollisionVolume((*it)->GetDefaultBSphere(), Colors::Aqua);

					if (MathTools::Intersect(*cellBox, (*it)->GetCollisionVolume()))
					{
						Visualizer::ShowCollisionVolume(*cellBox, Colors::Red);
						Visualizer::ShowCollisionVolume((*it)->GetCollisionVolume(), Colors::Red);
					}
					else
					{
						Visualizer::ShowCollisionVolume(*cellBox, Colors::Yellow);
					}

				}
				else
				{
					Visualizer::ShowCollisionVolume(*cellBox, Colors::Azure);
				}
			}

			TerrainRectangleArea test = TerrainRectangleArea(*it);
			test;
    }

}