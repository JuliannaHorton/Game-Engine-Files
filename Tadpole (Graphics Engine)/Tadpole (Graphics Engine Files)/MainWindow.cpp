//--------------------------------------------------------------------------------------
// File: MainWindow.cpp
//
// Heavily inspired by http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx
#include <WindowsX.h>
#include "resource.h"
#include "../Finalsprint/Polliwog Engine/Tadpole.h"
#include <assert.h>
#include "Engine.h"

//--------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------- 
Engine* g_dxapp = nullptr;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{ 
    hPrevInstance;
    lpCmdLine;
    //g_dxapp = new Tadpole();
    Tadpole& app = Tadpole::GetInstance();

    app.SetWindow(hInstance, nCmdShow);
    app.funRun();

    // Shutting down the app
    //delete g_dxapp;

    return 0;
}


