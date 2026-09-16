#include "ShaderTextureLight.h"
#include "ModelAttorney.h"
#include "ShaderColor.h"
#include "Model.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

#include "Texture.h"

ShaderTextureLight::ShaderTextureLight()
	: ShaderBase(L"../Assets/Shaders/ColorSelected.hlsl"), Tex(nullptr), shader(nullptr) //having trouble makign my own hlsl file, so I'm just gonna use ColorSelected
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16 , D3D11_INPUT_PER_VERTEX_DATA, 0 }, //<--- Took so long to notice this
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_Fog);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffFog);
	assert(SUCCEEDED(hr));



	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
	ZeroMemory(&PointLightData2, sizeof(PointLightData2));
	ZeroMemory(&SpotLightData2, sizeof(SpotLightData2));
	ZeroMemory(&PointLightData3, sizeof(PointLightData3));
	ZeroMemory(&SpotLightData3, sizeof(SpotLightData3));
}

ShaderTextureLight::~ShaderTextureLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBuffFog);

	if (PointLightMod != 0)
	{
		delete PointLightMod;
	}

	if (SpotLightMod != 0)
	{
		delete SpotLightMod;
	}
}

void ShaderTextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

void ShaderTextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData.Light.Ambient = amb;
	PointLightData.Light.Diffuse = dif;
	PointLightData.Light.Specular = sp;
	PointLightData.Position = pos;
	PointLightData.Attenuation = att;
	PointLightData.Range = r;

	if (PointLightMod == 0)
	{
		PointLightMod = new Model(Model::PreMadeModels::UnitSphere);
	}
	PointWorld = Matrix(SCALE, 2, 2, 2) * Matrix(TRANS, pos);
}

void ShaderTextureLight::SetPointLightParameters2(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData2.Light.Ambient = amb;
	PointLightData2.Light.Diffuse = dif;
	PointLightData2.Light.Specular = sp;
	PointLightData2.Position = pos;
	PointLightData2.Attenuation = att;
	PointLightData2.Range = r;
}

void ShaderTextureLight::SetPointLightParameters3(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData3.Light.Ambient = amb;
	PointLightData3.Light.Diffuse = dif;
	PointLightData3.Light.Specular = sp;
	PointLightData3.Position = pos;
	PointLightData3.Attenuation = att;
	PointLightData3.Range = r;
}

void ShaderTextureLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData.Light.Ambient = amb;
	SpotLightData.Light.Diffuse = dif;
	SpotLightData.Light.Specular = sp;
	SpotLightData.Position = pos;
	SpotLightData.Direction = dir;
	SpotLightData.Attenuation = att;
	SpotLightData.Range = r;
	SpotLightData.SpotExp = spotExp;

	if (SpotLightMod == 0)
	{
		SpotLightMod = new Model(Model::PreMadeModels::UnitPyramid);
	}

	Vect turn = dir - pos;
	turn.norm();
	float yaw = atan2(turn.X(), turn.Z());
	float roll = atan2(turn.Y(), turn.Z());
	float pitch = atan2(-turn.X(), sqrt(turn.Y() * turn.Y() + turn.Z() * turn.Z())); //This needs to optimized... sqrt is baaaaaadd

	SpotWorld = Matrix(SCALE, 2.5f, 4.5f, 2.5f) * Matrix(ROT_X, -roll) * Matrix(ROT_Y, -pitch) * Matrix(ROT_Z, -yaw) * Matrix(TRANS, pos);
}

void ShaderTextureLight::SetSpotLightParameters2(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData2.Light.Ambient = amb;
	SpotLightData2.Light.Diffuse = dif;
	SpotLightData2.Light.Specular = sp;
	SpotLightData2.Position = pos;
	SpotLightData2.Direction = dir;
	SpotLightData2.Attenuation = att;
	SpotLightData2.Range = r;
	SpotLightData2.SpotExp = spotExp;
}

void ShaderTextureLight::SetSpotLightParameters3(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData3.Light.Ambient = amb;
	SpotLightData3.Light.Diffuse = dif;
	SpotLightData3.Light.Specular = sp;
	SpotLightData3.Position = pos;
	SpotLightData3.Direction = dir;
	SpotLightData3.Attenuation = att;
	SpotLightData3.Range = r;
	SpotLightData3.SpotExp = spotExp;
}


void ShaderTextureLight::SendLightParameters(const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	dl.PntLight = PointLightData;
	dl.SptLight = SpotLightData;
	dl.PntLight2 = PointLightData2;
	dl.SptLight2 = SpotLightData2;
	dl.PntLight3 = PointLightData3;
	dl.SptLight3 = SpotLightData3;
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderTextureLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp, Texture* tex)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	//these are our lighting affects below

	mpTextureSRV = tex->GetTexture();
	mpSamplerState = tex->GetSamplier();


	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;
	this->SendFogData();

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderTextureLight::SendFogData(const float& start, const float& range, const Vect& color)
{
	Data_Fog wm;
	wm.FogStart = start;
	wm.FogRange = range;
	wm.FogColor = color;

	this->GetContext()->UpdateSubresource(mpBuffFog, 0, nullptr, &wm, 0, 0);
}

void ShaderTextureLight::SetToContext()
{
	ShaderBase::SetToContext_VS_PS_InputLayout();

	GetContext()->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	GetContext()->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	GetContext()->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	GetContext()->PSSetConstantBuffers(3, 1, &mpBuffFog);

	GetContext()->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	GetContext()->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	GetContext()->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	GetContext()->PSSetConstantBuffers(3, 1, &mpBuffFog);

	if (mpTextureSRV && mpSamplerState) //Skips if either are null (aka, no Texture was set)
	{
		GetContext()->PSSetShaderResources(0, 1, &mpTextureSRV);
		GetContext()->PSSetSamplers(0, 1, &mpSamplerState);
	}

}


void ShaderTextureLight::SetTexture(Texture* tex)
{
	Tex = tex;
	mpTextureSRV = tex->GetTexture();
	mpSamplerState = tex->GetSamplier();
}

void ShaderTextureLight::RenderLight(Matrix View, Matrix Proj)
{
	//shader->SetToContext();
	//shader->SendCamMatrices(View, Proj);

	////if (PointLightMod != 0)
	////{
	////	shader->SendWorldColor(PointWorld, Colors::Yellow);
	////	ModelAttorney::SetToContext(PointLightMod);
	////	PointLightMod->Render();
	////}

	//if (SpotLightMod != 0)
	//{
	//	shader->SendWorldColor(SpotWorld, Colors::Yellow);
	//	ModelAttorney::SetToContext(SpotLightMod);
	//	SpotLightMod->Render();
	//}
}

