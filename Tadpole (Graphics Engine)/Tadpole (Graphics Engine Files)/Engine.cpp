#include "Engine.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "RenderAttorney.h"
#include "LightAttorney.h"



Engine::Engine()
{
	mhMainWnd = nullptr;
	Window = {};

	BackgroundColor = Colors::MidnightBlue;
	mClientWidth = 960;
	mClientHeight = 540;
	mMainWndCaption = "Main Window";

	LightAttorney::SpotLoad();
	LightAttorney::PointLoad();
}

Engine::~Engine()
{
	RenderAttorney::MasterLock::Terminate();
}

void Engine::SetWindow(HINSTANCE hInstance, int nCmdShow)
{
	Initialize();

	mhMainWnd = RenderAttorney::MasterLock::SetInstance(hInstance, nCmdShow);

	RenderAttorney::MasterLock::SetWindow(mhMainWnd, mClientWidth, mClientHeight, this);
}

void Engine::run()
{
	LoadContent();
	resetTimer();

	MSG msg = { 0 };
	bool ReadyToExit = false;
	while (!ReadyToExit)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			ReadyToExit = ReadyToExit || (msg.message == WM_QUIT);
		}

		mTimer.Tick();
		CalculateFrameStats();

		Update();
		LightAttorney::UpdatePointLight();
		LightAttorney::UpdateSpotLight();

		RenderAttorney::MasterLock::GetContext()->ClearRenderTargetView(RenderAttorney::MasterLock::GetTargetView(), VasA(GetWindowColor()));
		RenderAttorney::MasterLock::GetContext()->ClearDepthStencilView(RenderAttorney::MasterLock::GetStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
		
		LightAttorney::DrawPointLight();
		LightAttorney::DrawSpotLight();
		Draw();
		// Switches the display to show the now-finished back-buffer
		RenderAttorney::MasterLock::GetSwapChain()->Present(SyncInterval, 0);
	}

	//Maybe this shouldn't be here
	LightAttorney::DirTerminate();
	LightAttorney::PointTerminate();
	LightAttorney::SpotTerminate();

	UnLoadContent();
}

void Engine::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	previousTime = totalTime;
	totalTime = mTimer.TotalTime();
	frameTime = totalTime - previousTime;

	// Compute averages over one second period.
	if (totalTime - targetTime >= 1)
	{
		std::ostringstream outs;
		outs.precision(5);
		outs << mMainWndCaption << "    "
			<< "FPS: " << (int)(1 / frameTime) << "    "
			<< "Frame Time: " << frameTime << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		targetTime = totalTime + 1;
	}
}


void Engine::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void Engine::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  Engine::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}

//
// --- Get GameTime ---
//

float Engine::GetFrameTime()
{
	return frameTime;
}


float Engine::GetTotalTime()
{
	return totalTime;
}

void Engine::resetTimer()
{
	mTimer.Reset();
}

//
// --- Get Window Info --- 
//

int Engine::GetWindowWidth()
{
	return mClientWidth;
}

int Engine::GetWindowHeight()
{
	return mClientHeight;
}

Vect Engine::GetWindowColor()
{
	return BackgroundColor;
}

void Engine::setWidthHeight(const int width, const int height)
{
	mClientWidth = width;
	mClientHeight = height;
}

void Engine::setWindowColor(Vect color)
{
	BackgroundColor = color;
}

void Engine::setWindowName(const char* pWindowName)
{
	mMainWndCaption = pWindowName;
}
