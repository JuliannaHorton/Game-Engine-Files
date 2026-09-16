#pragma once
// ShaderColorLight
// Andre Berthiaume, Feb 2017

#ifndef _SpriteShader
#define _SpriteShader

#include "ShaderBase.h"
#include "Matrix.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class SpriteShader : public ShaderBase
{

public:
	SpriteShader(const SpriteShader&) = delete;				 // Copy constructor
	SpriteShader(SpriteShader&&) = default;                    // Move constructor
	SpriteShader& operator=(const SpriteShader&) & = default;  // Copy assignment operator
	SpriteShader& operator=(SpriteShader&&) & = default;       // Move assignment operator
	~SpriteShader();		  							         // Destructor

	SpriteShader();

	virtual void SetToContext() override;;

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldandMaterial(const Matrix& world, Texture* tex, const RECT& size);


private:

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Vect CutRect;
		float imageWidth = 0;
		float imageHeight = 0;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;


	ID3D11ShaderResourceView* mpTextureSRV = nullptr;
	ID3D11SamplerState* mpSamplerState = nullptr;

};

#endif _SpriteShader

