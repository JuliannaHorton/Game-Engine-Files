#pragma once

#ifndef _VisualAttorney
#define _VisualAttorney

#include "Visualizer.h"
#include "../PollywogBog.h"

class VisualAttorney
{
public:
    class Sphere
    {
        friend class BSphereCmd;
        friend class CollisionBSphere;

        //Remove later, just need some easy access for testing
        friend class CollisionPairCmd;
        friend class CollisionSelfCmd;

    private:
        static void RenderBSphere(Matrix& S, const Vect& col) { Visualizer::RenderSphere(S, col); };
        static void ReturnBSphereCmd(BSphereCmd* c) { Visualizer::ReturnSphereCmd(c); };

        static void ShowBSphere(const CollisionBSphere& S, const Vect& col) { Visualizer::ShowBSphere(S, col); }; //Adds Command
    };

    class Box
    {
        friend class BoxCmd;
        friend class CollisionAABB;
        friend class CollisionOBB;
        friend class CollisionBSphere;

        //Remove later, just need some easy access for testing
        friend class CollisionPairCmd;
        friend class CollisionSelfCmd;

    private:
        static void RenderBox(Matrix& S, const Vect& col) { Visualizer::RenderBox(S, col); };
        static void ReturnBoxCmd(BoxCmd* c) { Visualizer::ReturnBoxCmd(c); };

        static void ShowAABB(const CollisionAABB& S, const Vect& col) { Visualizer::ShowAABB(S, col); }; //Adds Command
        static void ShowOBB(const CollisionOBB& S, const Vect& col) { Visualizer::ShowOBB(S, col); }; //Adds Command
    };

    class Engine
    {
        friend class Tadpole;

    private:
        static void VisualizeAll() { Visualizer::VisualizeAll(); };
        static void Terminate() { Visualizer::Terminate(); };
    };

};

#endif _VisualAttorney