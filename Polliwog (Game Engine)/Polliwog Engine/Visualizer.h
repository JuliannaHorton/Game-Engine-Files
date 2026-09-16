#pragma once

#ifndef _Visualizer
#define _Visualizer

#include "../PollywogBog.h"
#include <queue>

class CollisionVolume;
class CollisionBSphere;
class CollisionAABB;
class CollisionOBB;

class VisualizeCommand;
class VisualBSpherePool;
class VisualBoxPool;

class BSphereCmd;
class BoxCmd;
class OBBCmd;

class Visualizer
{
	friend class VisualAttorney;
private:
	static Visualizer* ptrInstance;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer();

	static Visualizer& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new Visualizer();
		return *ptrInstance;
	};

	static Vect Default_Color;
	GraphicObject_WireFrame* Sphere;
	GraphicObject_WireFrame* Box;

	//Can Visualize all Volumes
	void privShowCollisionVolume(const CollisionVolume& c, const Vect& col);
	void privShowBSphere(const CollisionBSphere& S, const Vect& col);
	void privShowAABB(const CollisionAABB& S, const Vect& col);
	void privShowOBB(const CollisionOBB& S, const Vect& col);
	void privShowPoint(const Vect& P1, const Vect& col);
	void privShowMinMax(const Vect& Max, const Vect& Min, const Vect& col);

	void privVisualizeAll();
	void privRenderBSphere(Matrix& S, const Vect& col);
	void privRenderBox(Matrix& S, const Vect& col);

	void privReturnSphereCmd(BSphereCmd* c);
	void privReturnBoxCmd(BoxCmd* c);

	//
	// Operates through a command pattern and command factory
	//
	using StorageList = std::queue<VisualizeCommand*>;
	StorageList myCommands;

	VisualBSpherePool* mySphereVisualPool;
	VisualBoxPool* myBoxVisualPool;

	static void VisualizeAll() { Instance().privVisualizeAll(); }; //Called by the engine

	// Accessed through visual attorney
	static void RenderSphere(Matrix& S, const Vect& col) { Instance().privRenderBSphere(S, col); };
	static void RenderBox(Matrix& S, const Vect& col) { Instance().privRenderBox(S, col); };
	static void ReturnSphereCmd(BSphereCmd* c) { Instance().privReturnSphereCmd(c); };
	static void ReturnBoxCmd(BoxCmd* c) { Instance().privReturnBoxCmd(c); };
	static void ShowBSphere(const CollisionBSphere& S, const Vect& col) { Instance().privShowBSphere(S, col); }; //Adds Command
	static void ShowAABB(const CollisionAABB& S, const Vect& col) { Instance().privShowAABB(S, col); }; //Adds Command
	static void ShowOBB(const CollisionOBB& S, const Vect& col) { Instance().privShowOBB(S, col); }; //Adds Command

	static void Terminate();

public:

	/// <summary>
	/// \brief Creates a Visual representation in-game of an volume (this willl be your collision boxes)
	/// \ingroup COLLISIONCONTROL
	///
	/// The Visual provides a useful representation of an Object's BSphere, making it easier how an object is colliding 
	/// <br>
	/// <br>
	/// First Set the object's collider model
	/// <br>
	/// \code 
	/// SetColliderModel(SpaceShip->getModel());
	/// \endcode
	/// Then call the ShowBSphere method whereever and with whatever color you'd like!
	/// <br>
	/// Although its most useful inside the Collision methods
	/// \code
	/// void Frigate::Collision(Cottage*)
	/// {
	///		DebugMsg::out("Collision Frigate with Cottage\n");
	///		Visualizer::ShowBSphere(GetBSphere(), Colors::Red);
	/// }
	/// \endcode
	/// Put Screenshot of what a Collision looks like!
	/// </summary>
	static void ShowCollisionVolume(const CollisionVolume& c, const Vect& col) { Instance().privShowCollisionVolume(c, col); };

	/// <summary>
	/// \brief Creates a Visual representation in-game of specific point in space (it will appear as a box
	/// \ingroup VISUALIZER
	///
	/// </summary>
	static void ShowPoint(const Vect& pos, const Vect& color) { Instance().privShowPoint(pos, color); };

	/// <summary>
	/// \brief Creates a Box from Min and Max values
	/// \ingroup VISUALIZER
	///
	/// </summary>
	static void ShowMinMax(const Vect& Max, const Vect& Min, const Vect& col) { Instance().privShowMinMax(Max, Min, col); };

};



#endif _Visualizer