// ShaderColorLight
// Andre Berthiaume, Feb 2017

#ifndef _ShaderTextureLight
#define _ShaderTextureLight

#include "ShaderBase.h"
#include "Matrix.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;
class Model;
class ShaderColor;

class ShaderTextureLight : public ShaderBase
{

public:
	ShaderTextureLight(const ShaderTextureLight&) = delete;				 // Copy constructor
	ShaderTextureLight(ShaderTextureLight&&) = default;                    // Move constructor
	ShaderTextureLight& operator=(const ShaderTextureLight&) & = default;  // Copy assignment operator
	ShaderTextureLight& operator=(ShaderTextureLight&&) & = default;       // Move assignment operator
	~ShaderTextureLight();		  							         // Destructor

	ShaderTextureLight();

	virtual void SetToContext() override;

	virtual void SetDirectionalLightParameters(const Vect& dir = Vect(0, 0, 0, 0), const Vect& amb = Vect(0, 0, 0, 0), const Vect& dif = Vect(0, 0, 0, 0), const Vect& sp = Vect(0, 0, 0, 0)) override;
	virtual void SetPointLightParameters(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) override;
	virtual void SetPointLightParameters2(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& amb = Vect(1, 1, 1, 0), const Vect& dif = Vect(1, 1, 1, 0), const Vect& sp = Vect(1, 1, 1, 0)) override;
	virtual void SetPointLightParameters3(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& amb = Vect(1, 1, 1, 0), const Vect& dif = Vect(1, 1, 1, 0), const Vect& sp = Vect(1, 1, 1, 0)) override;
	virtual void SetSpotLightParameters(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& dir = Vect(1, 1, 1, 0), float spotExp = 0, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) override;
	virtual void SetSpotLightParameters2(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& dir = Vect(1, 1, 1, 0), float spotExp = 0, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) override;
	virtual void SetSpotLightParameters3(const Vect& pos = Vect(1, 1, 1, 0), float r = 0, const Vect& att = Vect(1, 1, 1, 0), const Vect& dir = Vect(1, 1, 1, 0), float spotExp = 0, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) override;

	void SendFogData(const float& start = -1, const float& range = -1, const Vect& color = Vect(1, 1, 1, 0));


	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), Texture* tex = nullptr);
	void RenderLight(Matrix View, Matrix Proj);

	void SetTexture(Texture* tex);

private:

	Model* PointLightMod = nullptr;
	Matrix PointWorld;
	Model* SpotLightMod = nullptr;
	Matrix SpotWorld;
	ShaderTextureLight* shader;

	struct Material
	{
		Vect Ambient = Vect(0, 0, 0, 0);
		Vect Diffuse = Vect(0, 0, 0, 0);
		Vect Specular = Vect(0, 0, 0, 0);
	};

	struct PhongADS
	{
		Vect Ambient = Vect(0, 0, 0, 0);
		Vect Diffuse = Vect(0, 0, 0, 0);
		Vect Specular = Vect(0, 0, 0, 0);
	};



	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction = Vect(1, 1, 1);
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		float Range = 10;
	};

	PointLight PointLightData;

	struct PointLight2
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		float Range = 10;
	};

	PointLight2 PointLightData2;

	struct PointLight3
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		float Range = 10;
	};

	PointLight3 PointLightData3;


	struct SpotLight
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		Vect Direction = Vect(1, 1, 1);
		float SpotExp = 10;
		float Range = 10;
	};

	SpotLight SpotLightData;

	struct SpotLight2
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		Vect Direction = Vect(1, 1, 1);
		float SpotExp = 10;
		float Range = 10;
	};

	SpotLight2 SpotLightData2;

	struct SpotLight3
	{
		PhongADS Light;
		Vect Position = Vect(1, 1, 1);
		Vect Attenuation = Vect(1, 1, 1);
		Vect Direction = Vect(1,1,1);
		float SpotExp = 10;
		float Range = 10;
	};

	SpotLight3 SpotLightData3;


	//Buffers
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;


	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight;
		PointLight2 PntLight2;
		SpotLight2 SptLight2;
		PointLight3 PntLight3;
		SpotLight3 SptLight3;

		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;

	struct Data_Fog
	{
		float FogStart = -1;
		float FogRange = -1;
		//float4 FogColor = float4(.2,.2,.2, 1); // grey
		Vect FogColor = Vect(1, 1, 1, 0);

	};

	ID3D11Buffer* mpBuffFog;
	Texture* Tex;

	ID3D11ShaderResourceView* mpTextureSRV = nullptr;
	ID3D11SamplerState* mpSamplerState = nullptr;

};

#endif _ShaderTextureLight

