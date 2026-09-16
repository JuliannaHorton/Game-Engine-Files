#pragma once
// ShaderColorLight
// Andre Berthiaume, Feb 2017

#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class ShaderTexture : public ShaderBase
{

public:
	ShaderTexture(const ShaderTexture&) = delete;				 // Copy constructor
	ShaderTexture(ShaderTexture&&) = default;                    // Move constructor
	ShaderTexture& operator=(const ShaderTexture&) & = default;  // Copy assignment operator
	ShaderTexture& operator=(ShaderTexture&&) & = default;       // Move assignment operator
	~ShaderTexture();		  							         // Destructor

	ShaderTexture();

	virtual void SetToContext() override;

	void SendFogData(const float& start, const float& range, const Vect& color);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldandTexture(const Matrix& world, Texture* tex);

private:
	struct Material
	{
		Vect Ambient = Vect(1, 1, 1);
		Vect Diffuse = Vect(1, 1, 1);
		Vect Specular = Vect(1, 1, 1);
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

#endif _ShaderTexture

