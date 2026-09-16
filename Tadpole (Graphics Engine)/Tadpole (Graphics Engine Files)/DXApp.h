// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include "../DX Application/Engine.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"

class Model;
class SkyBox;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class ShaderTexture;
class GraphicObject_Texture;
class ShaderColorLight;
class GraphicObject_Light;
class ShaderTextureLight;
class GraphicObject_TextureLight;
class FireFlyShader;

class DXApp : public Engine, public Align16
{
private:	

	virtual void LoadContent();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();


	// Demo specific additions
	Camera mCam;

	float camSpeed;
	float rotSpeed;

	GraphicObject_Texture* Frigate;
	Model* pModel1;
	Matrix mWorld1;	

	Model* pModel2;
	Matrix mWorld2;

	Texture* FirgateTex;
	Texture* GridTex;

	ShaderColor*			pShaderCol;
	ShaderColorLight*		pShaderLit;
	ShaderTextureLight*		pShaderTexLit;
	ShaderTexture*		pShaderTex;


	FlatPlane* WorldPlane;
	Matrix FrigateRotTrans;
	Matrix FrigateScale;
	float FrigateRotSpeed;
	float FrigateSpeed;

public:
	DXApp() = default;
	virtual ~DXApp() = default;

};

#endif _DXApp