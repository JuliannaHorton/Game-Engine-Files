#pragma once

#ifndef _RenderAttorney
#define _RenderAttorney

#include "Renderer.h"

#include "Engine.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderBase.h"
#include "../src/Camera.h"
//#include "Image.h"

class RenderAttorney
{
public:
    friend class Model;
    friend class Texture;
    friend class ShaderBase;
    friend class Mirror;
    friend class Image;

private:
    static ID3D11DeviceContext* GetContext() { return Renderer::GetContext(); }
    static ID3D11Device* GetDevice() { return Renderer::GetDevice(); }

public:
    class MasterLock
    {
        friend class Engine;

    private:
        static ID3D11DeviceContext* GetContext() { return Renderer::GetContext(); }
        static ID3D11Device* GetDevice() { return Renderer::GetDevice(); }
        static IDXGISwapChain* GetSwapChain() { return Renderer::GetSwapChain(); }
        static ID3D11RenderTargetView* GetTargetView() { return Renderer::GetTargetView(); }
        static ID3D11DepthStencilView* GetStencilView() { return Renderer::GetStencilView(); }
        static void SetWindow(HWND hwnd, int w, int h, Engine* e) { Renderer::SetWindow(hwnd, w, h, e); }
        static HWND SetInstance(HINSTANCE hInstance, int nCmdShow) { return Renderer::SetInstance(hInstance, nCmdShow); };

        static void Terminate() { Renderer::Terminate(); }
    };

    class CameraStuff
    {
        friend class Camera;

    private:
        static D3D11_VIEWPORT GetViewport() { return Renderer::GetViewport(); }
        static void ResetViewport(D3D11_VIEWPORT newVP ) { Renderer::ResetViewport(newVP); }
    };

    class GraphicObjects
    {
        friend class GraphicObject_Sprite;
        friend class GraphicObject_WireFrame;

    private:
        static void SetToWireframe() { Renderer::SetToWireframe(); };
        static void SetToSolidframe() { Renderer::SetToSolidframe(); };

        static void BlendOn() { Renderer::BlendOn(); };
        static void BlendOff() { Renderer::BlendOff(); };
    };

};

#endif _RenderAttorney