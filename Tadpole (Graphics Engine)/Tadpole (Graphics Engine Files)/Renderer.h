
#ifndef _Renderer
#define _Renderer

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

#include "Engine.h"

class Engine;

class Renderer
{

public:
    friend class RenderAttorney; //Use Attorney to prevent user access to DX stuff

    static HWND GetWindow() { return Instance().privGetWindow(); };;

private:

    static Renderer* ptrInstance;

    Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    ~Renderer() = default;

    static Renderer& Instance()
    {
        if (ptrInstance == nullptr)
            ptrInstance = new Renderer();
        return *ptrInstance;
    };

    void ReportLiveDXObjects();

    void InitDirect3D();
    HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);


    // Main window handle
    //HWND      mhMainWnd;
    std::string mMainWndCaption;
    float mClientWidth;
    float mClientHeight;

    // DX application elements
    ID3D11Device* md3dDevice;					// Connects to the graphics card
    ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
    IDXGISwapChain* mSwapChain;					// image buffers used for rendering
    ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
    ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations
    ID3D11RasterizerState* FrontFaceAsCCWRS;
    D3D11_VIEWPORT vp;
    ID3D11BlendState* TransparentBS;
    ID3D11SamplerState* pSamplerState;

    HWND privGetWindow();

    //Getter methods
    ID3D11DeviceContext* privGetContext();
    static ID3D11DeviceContext* GetContext() { return Instance().privGetContext(); }; //For Attorney

    ID3D11Device* privGetDevice();
    static ID3D11Device* GetDevice() { return Instance().privGetDevice(); }; //For Attorney

    IDXGISwapChain* privGetSwapChain();
    static IDXGISwapChain* GetSwapChain() { return Instance().privGetSwapChain(); }; //For Attorney

    void privSetWindow(HWND hwnd, int w, int h, Engine* myEngine);
    static void SetWindow(HWND hwnd, int w, int h, Engine* myEngine) { Instance().privSetWindow(hwnd, w, h, myEngine); }; //For Attorney

    void privResetViewport(D3D11_VIEWPORT vp);
    static void ResetViewport(D3D11_VIEWPORT vp) { Instance().privResetViewport(vp); }; //For Attorney

    HWND privSetInstance(HINSTANCE hInstance, int nCmdShow);
    static HWND SetInstance(HINSTANCE hInstance, int nCmdShow) { return Instance().privSetInstance(hInstance, nCmdShow); }; //For Attorney

    ID3D11RenderTargetView* privGetTargetView();
    static ID3D11RenderTargetView* GetTargetView() { return Instance().privGetTargetView(); }; //For Attorney

    ID3D11DepthStencilView* privGetStencilView();
    static ID3D11DepthStencilView* GetStencilView() { return Instance().privGetStencilView(); }; //For Attorney

    D3D11_VIEWPORT privGetViewport();
    static D3D11_VIEWPORT GetViewport() { return Instance().privGetViewport(); }; //For Attorney

    //Settings
    void privSetToSolidframe();
    void privSetToWireframe();
    static void SetToWireframe() { Instance().privSetToWireframe(); };
    static void SetToSolidframe() { Instance().privSetToSolidframe(); };

    void privBlendOn();
    void privBlendOff();
    static void BlendOn() { Instance().privBlendOn(); };
    static void BlendOff() { Instance().privBlendOff(); };

    //Terminate/release 
    void privTerminate();
    static void Terminate() { Instance().privTerminate(); }; //For Attorney;
};




#endif _Renderer

