#pragma once

#ifndef _TerrainManager
#define _TerrainManager

#include "../PollywogBog.h"
#include <map>

class Terrain;

class TerrainManager
{
	friend class AssetAttorney;

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Default Polliwog Models
	/// </summary>
	/// <param name="name"></param>
	enum class DefaultTerrain
	{
		FlatTerrain
	};

private:
	static TerrainManager* ptrInstance;

	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	~TerrainManager() = default;

	static TerrainManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new TerrainManager();
		return *ptrInstance;
	};

	//
	// Methods for loading and Getting Assets
	//
	void privLoad(std::string name, Texture* heightMap, Texture* texture, int U, int V, float length, float maxHeight, float yValue); //name, specifications
	Terrain* privGet(std::string name);
	Terrain* privGet(DefaultTerrain Terrain);

	void privLoadDefaultResources();

	//
	// Data Structure: HashTable --- Stores loaded Models with a key string
	//
	static std::map<std::string, Terrain*> modelMap;
	//const std::string defaultPath = "Models/";

	static void Terminate();

	void findName(std::string name);
	static void LoadDefaultResources() { Instance().privLoadDefaultResources(); };

public:
	/// <summary>
	/// \ingroup TERRAIN
	/// \brief Saves and allows access to your models, based on the specified name and filepath in the parameters
	/// 
	/// Terrain can be defined by multiple values when 'loading' one in
	/// <br>
	/// First Texture is a HeightMap to define the height of the terrain
	/// <br>
	/// Second Texture is the actual image displayed on the terrain
	/// <br>
	/// The U,V integers represent how many times the image will be repreated
	/// <br> 
	/// Then length, maxHeight, and yValue defined the Terrain size and allowed height
	/// </summary>
	static void Load(std::string name, Texture* heightMap, Texture* texture, int U = 1, int V = 1, float length = 100, float maxHeight = 10, float yValue = 0) { Instance().privLoad(name, heightMap, texture, U, V, length, maxHeight, yValue); };
	/// <summary>
	/// \ingroup TERRAIN
	/// \brief Returns the requested Model
	/// </summary>
	static Terrain* Get(std::string name) { return Instance().privGet(name); };
	/// <summary>
	/// \ingroup TERRAIN
	/// \brief Returns the requested Default Model
	/// </summary>
	static Terrain* Get(DefaultTerrain ModelType) { return Instance().privGet(ModelType); };
};

#endif _TerrainManager
