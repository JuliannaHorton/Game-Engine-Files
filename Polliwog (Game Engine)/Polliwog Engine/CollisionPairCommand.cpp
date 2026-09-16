#include "CollisionPairCommand.h"
#include "CollisionDispatchBase.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionVolume.h"
#include "CollisionAABB.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "VisualAttorney.h"

CollisionPairCmd::~CollisionPairCmd()
{
    delete pDispatch;
    ColCollection.clear();
}

void CollisionPairCmd::execute()
{
    const DifCollidableCollection& Collection1 = pG1->GetColliderCollection(); //Hmm, doing wrong
    const DifCollidableCollection& Collection2 = pG2->GetColliderCollection();

    //Sometimes a collidable group is empty, such as with bullets when they have all left the scene
    if (!Collection1.empty())
        pG1->ComputeBox();
    if (!Collection2.empty())
        pG2->ComputeBox();

    const CollisionAABB& box2 = *pG1->getBox();
    const CollisionAABB& box = *pG2->getBox();

    //Test for the box
    if (MathTools::Intersect(box, box2)) //AABB box test
    {
        for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
        {
            const CollisionVolume& bs1 = (*it1)->GetCollisionVolume();
            const CollisionBSphere& Sphere1 = (*it1)->GetDefaultBSphere();

            for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
            {
                const CollisionVolume& bs2 = (*it2)->GetCollisionVolume();
                const CollisionBSphere& Sphere2 = (*it2)->GetDefaultBSphere();

                //Test for sphere
                if (MathTools::Intersect(Sphere1, Sphere2)) //BSphere Test
                {

                    //Test for user-volume 
                    if (MathTools::Intersect(bs1, bs2))
                    {
                        pDispatch->ProcessCallbacks(*it1, *it2);
                        //Visualizer::ShowCollisionVolume(bs1, Colors::Red);
                        //Visualizer::ShowCollisionVolume(bs2, Colors::Red);

                    }
                    else
                    {
                        //Visualizer::ShowCollisionVolume(bs1, Colors::Blue);
                        //Visualizer::ShowCollisionVolume(bs2, Colors::Blue);
                    }

                    //VisualAttorney::Sphere::ShowBSphere(Sphere1, Colors::Red);
                    //VisualAttorney::Sphere::ShowBSphere(Sphere2, Colors::Red);
                }
                else
                {
                    //VisualAttorney::Sphere::ShowBSphere(Sphere1, Colors::Cyan);
                    //VisualAttorney::Sphere::ShowBSphere(Sphere2, Colors::Cyan);
                }

            }
        }
        //VisualAttorney::Box::ShowAABB(box, Colors::Red);
        //VisualAttorney::Box::ShowAABB(box2, Colors::Red);
    }
    else
    {
        //VisualAttorney::Box::ShowAABB(box, Colors::Green);
        //VisualAttorney::Box::ShowAABB(box2, Colors::Green);
    }
}