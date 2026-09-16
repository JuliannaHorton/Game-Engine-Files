#pragma once
// ShaderColorLight
// Andre Berthiaume, Feb 2017

#ifndef _TestFlatPlane
#define _TestFlatPlane

#include "ShaderBase.h"
#include "Matrix.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class TestFlatPlane : public ShaderBase
{

public:
	TestFlatPlane(const TestFlatPlane&) = delete;				 // Copy constructor
	TestFlatPlane(TestFlatPlane&&) = default;                    // Move constructor
	TestFlatPlane& operator=(const TestFlatPlane&) & = default;  // Copy assignment operator
	TestFlatPlane& operator=(TestFlatPlane&&) & = default;       // Move assignment operator
	~TestFlatPlane();		  							         // Destructor

	TestFlatPlane();

	virtual void SetToContext() override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& dir = Vect(1, 1, 1, 0), float spotExp = 0, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SendFogData(const float& start, const float& range, const Vect& color);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldandTexture(const Matrix& world, Texture* tex);

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};


	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;


	struct Data_Fog
	{
		float FogStart = -1;
		float FogRange = -1;
		//float4 FogColor = float4(.2,.2,.2, 1); // grey
		Vect FogColor = Vect(1, 1, 1, 0);

	};

	ID3D11Buffer* mpBuffFog;

	ID3D11ShaderResourceView* mpTextureSRV = nullptr;
	ID3D11SamplerState* mpSamplerState = nullptr;

};

#endif _TestFlatPlane

