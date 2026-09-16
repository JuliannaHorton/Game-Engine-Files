#include "Visualizer.h"
#include "VisualizeCommand.h"
#include "BSphereCmd.h"
#include "BoxCmd.h"
#include "CollisionBSphere.h"
#include "CollisionAABB.h"
#include "CollisionVolume.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "VisualBSpherePool.h"
#include "VisualBoxPool.h"
#include "CollisionOBB.h"
#include "SceneManager.h"

Visualizer* Visualizer::ptrInstance = nullptr;

Visualizer::Visualizer()
{
	mySphereVisualPool = new VisualBSpherePool();
	myBoxVisualPool = new VisualBoxPool();

	Vect Col = Colors::Blue;

	//Only two graphic objects are required for rendering
	Sphere = new GraphicObject_WireFrame(ShaderManager::Get(ShaderManager::DefaultShaders::PolliwogColorRender), ModelManager::Get("ModelSphere"), Col);
	Box = new GraphicObject_WireFrame(ShaderManager::Get(ShaderManager::DefaultShaders::PolliwogColorRender), ModelManager::Get("Box"), Col);
}

Visualizer::~Visualizer()
{
	delete myBoxVisualPool;
	delete mySphereVisualPool;

	delete Sphere;
	delete Box;
}

void Visualizer::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void Visualizer::privVisualizeAll() //Loops through commands
{
	VisualizeCommand* c;

	while (!myCommands.empty())
	{
		c = myCommands.front();
		c->execute();

		myCommands.pop();
		c->returnCmd();
	}
}

void Visualizer::privShowBSphere(const CollisionBSphere& S, const Vect& col)
{
	Vect vBSSize = S.GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = S.GetCenter();;

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix World = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos);

	BSphereCmd* cmd = mySphereVisualPool->GetVisual();
	cmd->setVisual(World, col);

	myCommands.push(cmd);
}

void Visualizer::privShowAABB(const CollisionAABB& S, const Vect& col)
{

	Vect United = S.GetMin() + S.GetMax();
	Vect AABBPos = Vect(United.X() * 0.5f, United.Y() * 0.5f, United.Z() * 0.5f, United.W()); //Translation: (Min + Max)/2
	Vect AABBSize = S.GetMax() - S.GetMin(); //Scale 

	//Create world matrix
	Matrix World = Matrix(SCALE, AABBSize) * Matrix(TRANS, AABBPos);

	//Box Command
	BoxCmd* cmd = myBoxVisualPool->GetVisual();
	cmd->setVisual(World, col);

	myCommands.push(cmd);
}

void Visualizer::privShowOBB(const CollisionOBB& S, const Vect& col)
{
	//Calculating local
	Vect United = S.GetMax() + S.GetMin();
	Vect OBBPos = Vect(United.X() * 0.5f, United.Y() * 0.5f, United.Z() * 0.5f, United.W()); //Translation: (Min + Max)/2
	Vect OBBSize = (S.GetMax() - S.GetMin()); //Scale 

	//Create world matrix with Local and then original World
	Matrix World = Matrix(SCALE, OBBSize) * Matrix(TRANS, OBBPos) * S.GetMatrix(); //Multiply by original world matrix... This seems wrong 

	//Box Command
	BoxCmd* cmd = myBoxVisualPool->GetVisual();
	cmd->setVisual(World, col);

	myCommands.push(cmd);
}

void Visualizer::privShowCollisionVolume(const CollisionVolume& c, const Vect& col)
{
	c.DebugView(col);
}


void Visualizer::privShowPoint(const Vect& P1, const Vect& col)
{
	Vect Max = Vect(P1.X() + 1, P1.Y() + 1, P1.Z() + 1);
	Vect Min = Vect(P1.X() - 1, P1.Y() - 1, P1.Z() - 1);

	Vect United = Max + Min;
	Vect AABBPos = Vect(United.X() * 0.5f, United.Y() * 0.5f, United.Z() * 0.5f, United.W()); //Translation: (Min + Max)/2
	Vect AABBSize = Max - Min; //Scale 

	//Create world matrix
	Matrix World = Matrix(SCALE, AABBSize) * Matrix(TRANS, AABBPos);

	//AABB Command
	BoxCmd* cmd = myBoxVisualPool->GetVisual();
	cmd->setVisual(World, col);

	myCommands.push(cmd);
}


void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	Sphere->SetColor(col);

	Sphere->SetWorld(S);
	Sphere->Render(SceneManager::getCurrentScene()->getCamera());
}

void Visualizer::privRenderBox(Matrix& S, const Vect& col)
{
	Box->SetColor(col);

	Box->SetWorld(S);
	Box->Render(SceneManager::getCurrentScene()->getCamera());
}

void Visualizer::privReturnSphereCmd(BSphereCmd* c)
{
	mySphereVisualPool->ReturnVisual(c);
}

void Visualizer::privReturnBoxCmd(BoxCmd* c)
{
	myBoxVisualPool->ReturnVisual(c);
}

void Visualizer::privShowMinMax(const Vect& Max, const Vect& Min, const Vect& col)
{

	Vect United = Max + Min;
	Vect AABBPos = Vect(United.X() * 0.5f, United.Y() * 0.5f, United.Z() * 0.5f, United.W()); //Translation: (Min + Max)/2
	Vect AABBSize = Max - Min; //Scale 

	//Create world matrix
	Matrix World = Matrix(SCALE, AABBSize) * Matrix(TRANS, AABBPos);

	//AABB Command
	BoxCmd* cmd = myBoxVisualPool->GetVisual();
	cmd->setVisual(World, col);

	myCommands.push(cmd);
}
