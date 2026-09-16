#include "CollisionSelfCommand.h"
#include "CollisionDispatchBase.h"
#include "CollisionBSphere.h"
#include "CollisionVolume.h"
#include "CollidableGroup.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "Collidable.h"

CollisionSelfCmd::~CollisionSelfCmd()
{
    delete pDispatch;
}

void CollisionSelfCmd::execute()
{
    const DifCollidableCollection& Collection = pG->GetColliderCollection();



    for (auto Object1 = Collection.begin(); Object1 != Collection.end(); Object1++)
    {
        const CollisionVolume& bs1 = (*Object1)->GetCollisionVolume();
        const CollisionBSphere& Sphere1 = (*Object1)->GetDefaultBSphere();

        for (auto Object2 = std::next(Object1); Object2 != Collection.end(); Object2++)
        {
            const CollisionVolume& bs2 = (*Object2)->GetCollisionVolume();
            const CollisionBSphere& Sphere2 = (*Object2)->GetDefaultBSphere();

            if (MathTools::Intersect(Sphere1, Sphere2))
            {
                if (MathTools::Intersect(bs1, bs2))
                {
                    Visualizer::ShowCollisionVolume(bs1, Colors::Red);
                    Visualizer::ShowCollisionVolume(bs2, Colors::Red);

                    pDispatch->ProcessCallbacks(*Object1, *Object2);
                }
            }
        }
    }
}