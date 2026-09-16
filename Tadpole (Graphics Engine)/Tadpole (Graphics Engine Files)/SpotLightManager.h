#pragma once

#ifndef _SpotLightManager
#define _SpotLightManager

#include <map>
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Matrix.h"

class ShaderTextureLight;
class ShaderColorLight;
class ShaderColor;
class ShaderBase;

class Model;

class SpotLightManager
{
	friend class LightAttorney;

public:

	struct SpotLight
	{
		ShaderBase* shader = nullptr;
		Vect pos;
		Vect dir;
		Vect amb;
		Vect dif;
		Vect sp;
		float r = 0;
		Vect att;
	};

private:

	//Model* Sphere = nullptr;
	//Matrix ModelWorld;
	//Matrix ModelRot;
	//Model* Arrow = nullptr;
	//ShaderColor* shader;

	//Matrix V;
	//Matrix P;
	//int mode;

	static SpotLightManager* ptrInstance;

	SpotLightManager();
	SpotLightManager(const SpotLightManager&) = delete;
	SpotLightManager& operator=(const SpotLightManager&) = delete;
	~SpotLightManager();

	static SpotLightManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new SpotLightManager();
		return *ptrInstance;
	};


	static std::map<int, SpotLight*> lightMap;

	void privMoveLight(ShaderBase* shader, int name, const Vect& newPos);
	void privTurnLight(ShaderBase* shader, int name, const Vect& newPos);
	void privUpdateLight(ShaderBase* shader, int name, const Vect& pos, const Vect& dir, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1));

	Vect privGetPos(int name);
	Vect privGetDir(int name);

	void privRemoveLight(int name);
	void findLight(int name);

	void privUpdate();
	void privDraw();

	// Update and Draw were for the model's I had representing the different light sources
	static void Update() //Accessed by the engine
	{
		Instance().privUpdate();
	}

	static void Draw() //Accessed by the engine 
	{
		Instance().privDraw();
	}



	void privSendCamInfo(Matrix View, Matrix Proj, int lightMode); // Originally for the light models, now doesn't do anything

	// Load in the 3 light's for the user to control
	void privLoadLights();
	static void LoadLights() //Accessed by the engine
	{
		Instance().privLoadLights();
	}


	void privTerminate();
	static void Terminate() { Instance().privTerminate(); }; //Accessed by the engine


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
	/// \brief Updates the light's direction
	/// \ingroup LIGHTS
	///	
	/// </summary>
	static void TurnLight(ShaderBase* shader, int name, const Vect& newDir)
	{
		Instance().privTurnLight(shader, name, newDir);
	};

	/// <summary>
	/// \brief Updates a PointLight
	/// \ingroup LIGHTS
	///	
	/// If the light is never updated it will effectively be off, until it is. 
	/// If provided with no peramitters default one's will be applied.
	/// </summary>
	static void UpdateLight(ShaderBase* shader, int name, const Vect& pos, const Vect& dir, const Vect& amb = Colors::White, const Vect& dif = Colors::White, const Vect& sp = Vect(1, 1, 1), const float r = 100, const Vect& att = Vect(1, 1, 1))
	{
		Instance().privUpdateLight(shader, name, pos, dir, amb, dif, sp, r, att);
	};

	static void RemoveLight(int name)
	{
		Instance().privRemoveLight(name);
	}


	//
	// Accessors 
	//

	static Vect GetPos(int name)
	{
		return Instance().privGetPos(name);
	};

	static Vect GetDir(int name)
	{
		return Instance().privGetDir(name);
	};

	static void SendCamInfo(Matrix View, Matrix Proj, int lightMode)
	{
		Instance().privSendCamInfo(View, Proj, lightMode);
	}

};

#endif _SpotLightManager