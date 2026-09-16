#include "Tadpole.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "../Finalsprint/Polliwog Engine/ImageAttorney.h"

#include "../Finalsprint/Polliwog Engine/AssetAttorney.h"

#include "../Finalsprint/Polliwog Engine/SceneManagerAttorney.h"
#include "../Finalsprint/Polliwog Engine/TimeManagerAttorney.h"
#include "../Finalsprint/Polliwog Engine/CameraManager.h"
#include "../Finalsprint/Polliwog Engine/VisualAttorney.h"
#include "../Finalsprint/Polliwog Engine/FontManAttorney.h"
#include "../Finalsprint/Polliwog Engine/ScreenLogAttorney.h"

Tadpole* Tadpole::ptrInstance = nullptr;

Tadpole& Tadpole::GetInstance() {
	if (ptrInstance == nullptr) {
		ptrInstance = new Tadpole();
	}
	return *ptrInstance;
}

void Tadpole::Initialize()
{
	//mCam = new CameraManager();
	this->GameInitialize();
}

void Tadpole::LoadContent()
{
	// Load in Default Polliwog Resources
	AssetAttorney::Engine::LoadModelResources();
	AssetAttorney::Engine::LoadShaderResources();

	// Load in User Resources
	this->LoadResources();
}

void Tadpole::Update()
{

	TimeManagerAttorney::Engine::ProcessTime();

	SceneManagerAttorney::Engine::Update();

}

void Tadpole::Draw()
{
	VisualAttorney::Engine::VisualizeAll();

	SceneManagerAttorney::Engine::Draw();

	ScreenLogAttorney::Engine::Render();
}

void Tadpole::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);

}

void Tadpole::UnLoadContent()
{
	AssetAttorney::Engine::ModelTerminate();
	AssetAttorney::Engine::ShaderTerminate();
	AssetAttorney::Engine::TextureTerminate();
	AssetAttorney::Engine::TerrainTerminate();
	VisualAttorney::Engine::Terminate();
	ImageAttorney::Engine::Terminate();
	FontManAttorney::Engine::Terminate();
	ScreenLogAttorney::Engine::Terminate();
	TimeManagerAttorney::Engine::Terminate();
	SceneManagerAttorney::Engine::Terminate();

	this->GameEnd();
}


//
// Time Methods
//
float Tadpole::GetTime()
{
	return Instance().GetTotalTime();
}

//
// Window Methods
//
int Tadpole::privGetWidth()
{
	return this->GetWindowWidth(); //Get window width
}

int Tadpole::privGetHeight()
{
	return this->GetWindowHeight(); //Get window height
}

Vect Tadpole::privGetWindowColor()
{
	return WindowColor;
}

const char* Tadpole::privGetWindowName()
{
	return name;
}

void Tadpole::privSetWindowName(const char* n)
{
	this->setWindowName(n);
	name = n;
}

void Tadpole::privSetWindowSize(int w, int h)
{
	this->setWidthHeight(w, h);
}

void Tadpole::privSetWindowColor(float r, float g, float b, float o)
{
	WindowColor = Vect(r, g, b, o);
	this->setWindowColor(WindowColor); //Red, Green, Blue, Opacity
}

void Tadpole::privSetWindowColor(Vect Color)
{
	WindowColor = Color;
	this->setWindowColor(WindowColor);
}

//
// Final Terminate --- Called in 'main.cpp'
//
void Tadpole::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
