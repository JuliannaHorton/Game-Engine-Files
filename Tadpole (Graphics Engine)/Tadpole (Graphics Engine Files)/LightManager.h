#pragma once

#ifndef _LightManager
#define _LightManager

#include <map>
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

class ShaderTextureLight;
class ShaderColorLight;

class Model;

class LightManager
{
	friend class AssetAttorney;

public:

	enum class lightType
	{
		Directional,
		Spot,
		Point
	};

	struct DirectionalLight
	{
		ShaderTextureLight* shader;
		Vect dir;
		Vect amb;
		Vect dif;
		Vect sp;
	};

	struct SpotLight
	{
		ShaderTextureLight* shader;
		Vect pos;
		Vect dir;
		Vect amb;
		Vect dif;
		Vect sp;
		float r;
		Vect att;
	};

	struct PointLight
	{
		ShaderTextureLight* shader;
		Vect pos;
		Vect amb;
		Vect dif;
		Vect sp;
		float r;
		Vect att;
	};

private:

	Model* Sphere = nullptr;
	Model* Pyramid = nullptr;
	Model* Arrow = nullptr;

	static LightManager* ptrInstance;

	LightManager() = default;
	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;
	~LightManager() = default;

	static LightManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new LightManager();
		return *ptrInstance;
	};

	//
	// Methods for loading and Getting Assets
	//

	//
	// Data Structure: HashTable --- Stores loaded Models with a key string
	//
	static std::map<int, DirectionalLight*> lightMap;
	static std::map<int, SpotLight*> lightMap;
	static std::map<int, PointLight*> lightMap;

	void privCreateDirectionalLight(ShaderTextureLight* shader, int name, const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void privMoveDirectionalLight(int name, const Vect& newDir);
	void privUpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1));

	void privCreatePointLight(ShaderTextureLight* shader, int name, const Vect& pos, const Vect& amb = Colors::White, const Vect& dif = Colors::White, const Vect& sp = Vect(1, 1, 1), const float r = 100, const Vect& att = Vect(1, 1, 1));
	void privMovePointLight(int name, const Vect& newPos);
	void privUpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1));

	void privCreateSpotLight(ShaderTextureLight* shader, int name, const Vect& pos, const Vect& dir, const Vect& amb = Colors::White, const Vect& dif = Colors::White, const Vect& sp = Vect(1, 1, 1), const float r = 100, const Vect& att = Vect(1, 1, 1));
	void privMoveSpotLight(int name, const Vect& newPos);
	void privUpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1));


	static void Terminate();



public:
	//static void Load(std::string name, std::string modelPath) { Instance().privLoad(name, modelPath); };

	static void CreateDirectionalLight(ShaderTextureLight* shader, int name, const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1))
		{ Instance().privCreateDirectionalLight(shader, name, dir, amb, dif, sp); };
	static void MoveDirectionalLight(int name, const Vect& newDir)
		{ Instance().privMoveDirectionalLight(name, newDir); };
	static void UpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1))
		{ Instance().privUpdateLight(name, newAmb, newDif, newSp); };

	static void CreatePointLight(ShaderTextureLight* shader, int name, const Vect& pos, const Vect& amb = Colors::White, const Vect& dif = Colors::White, const Vect& sp = Vect(1, 1, 1), const float r = 100, const Vect& att = Vect(1, 1, 1))
		{ Instance().privCreatePointLight(shader, name, pos, amb, dif, sp, r, att); };
	static void MovePointLight(int name, const Vect& newPos)
		{ Instance().privMoveDirectionalLight(name, newPos); };
	static void UpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1))
		{ Instance().privUpdateLight(name, newAmb, newDif, newSp, newR, newAtt); };

	static void CreateSpotLight(ShaderTextureLight* shader, int name, const Vect& pos, const Vect& dir, const Vect& amb = Colors::White, const Vect& dif = Colors::White, const Vect& sp = Vect(1, 1, 1), const float r = 100, const Vect& att = Vect(1, 1, 1))
		{ Instance().privCreateSpotLight(shader, name, pos, dir, amb, dif, sp, r, att); };
	static void MoveSpotLight(int name, const Vect& newPos)
		{ Instance().privMoveSpotLight(name, newPos); };
	static void UpdateLight(int name, const Vect& newAmb = Colors::White, const Vect& newDif = Colors::White, const Vect& newSp = Vect(1, 1, 1), const float newR = 100, const Vect& newAtt = Vect(1, 1, 1))
		{ Instance().privUpdateLight(name, newAmb, newDif, newSp, newR, newAtt); };

};

#endif _LightManager