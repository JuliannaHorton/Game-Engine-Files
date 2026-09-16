#pragma once

#ifndef _LightManager
#define _LightManager

#include <map>
#include "d3dUtil.h"
#include <d3dUtil.h>
#include <assert.h>
#include "Matrix.h"

class ShaderTextureLight;
class ShaderColorLight;
class ShaderColor;
class ShaderBase;

class Model;

class PointLightManager
{
	friend class LightAttorney;

public:

	struct PointLight
	{
		ShaderBase* shader = nullptr;
		Vect pos = Vect(0, 0, 0);
		Vect amb = Vect(0, 0, 0);
		Vect dif = Vect(0, 0, 0);
		Vect sp = Vect(0,0,0);
		float r = 0;
		Vect att = Vect(0, 0, 0);
	};

private:

	Model* Sphere = nullptr;
	Matrix ModelWorld;
	Model* Arrow = nullptr;
	//ShaderColor* shader;

	// Only really needed for visual models
	Matrix V;
	Matrix P;
	int mode;

	static PointLightManager* ptrInstance;

	PointLightManager();
	PointLightManager(const PointLightManager&) = delete;
	PointLightManager& operator=(const PointLightManager&) = delete;
	~PointLightManager();

	static PointLightManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new PointLightManager();
		return *ptrInstance;
	};


	static std::map<int, PointLight*> lightMap;

	void privMoveLight(ShaderBase* shader, int name, const Vect& newPos);
	void privUpdateLight(ShaderBase* shader, int name, const Vect& pos, const Vect& amb = .1 * Vect(1, 1, 1), const Vect& dif = 2 * Vect(1, 1, 1), const Vect& sp = 1 * Vect(1, 1, 1), const float r = 100, const Vect& att = .2 * Vect(0, 1, 0));

	Vect privGetPos(int name);

	void privRemoveLight(int name);
	void findLight(int name);

	void privLoadLights();

	// To be moved to 
	void privTerminate();
	static void Terminate() { Instance().privTerminate(); };
	void privUpdate();
	void privDraw();

	static void Update()
	{
		Instance().privUpdate();
	}

	static void Draw()
	{
		Instance().privDraw();
	}

	void privSendCamInfo(Matrix View, Matrix Proj, int lightMode);

	static void LoadLights()
	{
		Instance().privLoadLights();
	}

public:

	/// <summary>
	/// \brief Updates the light's Position
	/// \ingroup LIGHTS
	///	
	/// </summary>
	/// 
	static void MoveLight(ShaderBase* shader, int name, const Vect& newPos)
	{
		Instance().privMoveLight(shader, name, newPos);
	};

	/// <summary>
	/// \brief Updates a SpotLight
	/// \ingroup LIGHTS
	///	
	/// If the light is never updated it will effectively be off, until it is. 
	/// If provided with no peramitters default one's will be applied.
	/// </summary>
	///
	static void UpdateLight(ShaderBase* shader, int name, const Vect& pos, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1))
	{
		Instance().privUpdateLight(shader, name, pos, newAmb, newDif, newSp, newR, newAtt);
	};

	/// <summary>
	/// \brief Returns the light's position
	/// \ingroup LIGHTS
	///	
	/// </summary>
	/// 
	static Vect GetPos(int name)
	{
		return Instance().privGetPos(name);
	};

	/// <summary>
	/// \brief Removes a SpotLight
	/// \ingroup LIGHTS
	///	
	/// </summary>
	/// 
	static void RemoveLight(int name)
	{
		Instance().privRemoveLight(name);
	}

	static void SendCamInfo(Matrix View, Matrix Proj, int lightMode) //Doesn't really do anything rn (was originally for when I had models)
	{
		Instance().privSendCamInfo(View, Proj, lightMode);
	}
	

};

#endif _PointLightManager