
#ifndef _Engine
#define _Engine

// Bang
#include <WindowsX.h>
#include "resource.h"
#include "Align16.h"
#include "GameTimer.h"
#include <assert.h>
#include <sstream>
#include "d3dUtil.h" 


#include <d3d11.h>
#include <string>


#include "Renderer.h"

#define ENGINE_WINDOW_NAME_LENGTH 128

class Engine
{
public:
    Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    virtual ~Engine();


    // User control
    virtual void Initialize() = 0;
    virtual void LoadContent() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void UnLoadContent() = 0;

    // Set-Up
    void run();
    void SetWindow(HINSTANCE hInstance, int nCmdShow);

    // Getter and Setter
    float GetFrameTime();
    float GetTotalTime();
    void resetTimer();

    int GetWindowWidth();
    int GetWindowHeight();
    Vect GetWindowColor();

    void setWidthHeight(const int width, const int height);
    void setWindowColor(Vect color);
    void setWindowName(const char* pWindowName);

    virtual void OnMouseDown(WPARAM btnState, int xval, int yval) = 0;
    static void OnMouseUp(WPARAM btnState, int xval, int yval);
    static void OnMouseMove(WPARAM btnState, int xval, int yval);
    static void OnMouseWheel(short delta);
    //static void getMousePosition(int& x, int& y);




    // private: --------------------------------------
private:
    HWND      mhMainWnd;

    GameTimer mTimer;
    void CalculateFrameStats();

    float previousTime = 0;
    float frameTime = 0;
    float totalTime = 0;
    float targetTime = 0.0f;

    std::string mMainWndCaption;
    RECT Window;
    int mClientWidth;
    int mClientHeight;

    Vect BackgroundColor;
    int SyncInterval = 1;  // 1 for sync to monitor refresh rate, 0 for no sync
};




#endif _Engine

