#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "../DX Application/GraphicObject_Texture.h"
#include "../DX Application/ShaderTexture.h"
#include "ShaderColorLight.h"
#include "../DX Application/GraphicObject_ColorLight.h"
#include "../DX Application/ShaderTextureLight.h"
#include "../DX Application/GraphicObject_TextureLight.h"
#include "../DX Application/SkyBox.h"
#include "../DX Application/Mirror.h"
#include "../DX Application/FireFly.h"
#include "../DX Application/FireFlyShader.h"

#include "../DX Application/Keyboard.h"
#include "../DX Application/Mouse.h"

void DXApp::Initialize()
{
	this->setWindowName("Matrices and Movement");
	this->setWindowColor(Colors::Aqua);

	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	this->setWidthHeight((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);  // 1/4 of the screen
}

void DXApp::LoadContent()
{
	mCam.setPerspective(3.14159 / 3, GetWindowWidth() / GetWindowHeight(), 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 3, -5));

	pShaderTex = new ShaderTexture();
	pShaderLit = new ShaderColorLight();
	pShaderTexLit = new ShaderTextureLight();


	FirgateTex = new Texture(L"../Assets/Textures/space_frigate.tga");
	GridTex = new Texture(L"../Assets/Textures/grid.tga");

	// Initialize the world matrix
	FrigateScale = Matrix(SCALE, .2f, .2f, .2f);
	FrigateRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 5, 0);
	mWorld1 = FrigateScale * Matrix(TRANS, 0, 5, 0);
	mWorld2 = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 0, 0, 0);

	Vect center = Vect(-72, 0, 45);
	Vect CamCenter;
	mCam.getPos(CamCenter);

	//
	// Models and Graphic Objects
	//
	pModel1 = new Model("../Assets/Models/space_frigate.azul");
	pModel2 = new Model("../Assets/Models/PineTree1.azul");

	Frigate = new GraphicObject_Texture(pShaderTex, pModel1); //Cabin
	Frigate->SetTexture(FirgateTex);
	Frigate->SetWorld(mWorld1);

	WorldPlane = new FlatPlane(100, 1, 1);

	float x;
	float y;
	Mouse::GetCursor(x, y);

	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(26.1, 9.71, -11.67), Vect(27, 10, -12));
}

void DXApp::Update()
{
	mWorld1 = FrigateScale * FrigateRotTrans;
	Frigate->SetWorld(mWorld1);

	//
	// --- Camera Position ---
	//

	float boost = 1;
	if (GetKeyState(VK_LSHIFT) & 0x08000) { boost = 10; }

	float camSpeed = 3.0f * GetFrameTime() * boost;
	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_W))
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_S))
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_A))
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_D))
	{
		mCam.TranslateLeftRight(camSpeed);
	}


	float rotSpeed = 0.6f * GetFrameTime() * boost;
	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_LEFT))
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_RIGHT))
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_UP))
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_DOWN))
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	//
	// Frigate Position
	//

	//Why do I need the FrameTime?
	FrigateSpeed = 3 * GetFrameTime() * boost;
	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_I))
	{
		FrigateRotTrans = Matrix(TRANS, Vect(0, 0, FrigateSpeed)) * FrigateRotTrans;
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_K))
	{
		FrigateRotTrans = Matrix(TRANS, Vect(0, 0, -FrigateSpeed)) * FrigateRotTrans;
	}

	FrigateRotSpeed = 1 * GetFrameTime() * boost;
	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_J))
	{
		FrigateRotTrans = Matrix(ROT_Y, FrigateRotSpeed) * FrigateRotTrans;
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_L))
	{
		FrigateRotTrans = Matrix(ROT_Y, -FrigateRotSpeed) * FrigateRotTrans;
	}



	mCam.updateCamera();
}

void DXApp::Draw()
{

	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderTex->SetToContext();
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	pShaderTex->SendWorldandTexture(mWorld1, FirgateTex);
	Frigate->Render();

	pShaderTex->SendWorldandTexture(mWorld2, GridTex);
	WorldPlane->Render();

}

void DXApp::UnLoadContent()
{
	delete pModel1;
	delete pModel2;

	delete pShaderTex;
	delete pShaderLit;
	delete pShaderTexLit;

	delete FirgateTex;
	delete GridTex;

	delete Frigate;

	delete WorldPlane;
}
