#include "TerrainManager.h"
#include "../Polliwog Engine/Terrain.h"
#include "../Polliwog Engine/TextureManager.h"
#include <iostream>

TerrainManager* TerrainManager::ptrInstance = nullptr;
std::map<std::string, Terrain*> TerrainManager::modelMap;

void TerrainManager::privLoad(std::string name, Texture* heightMap, Texture* texture, int U, int V, float length, float maxHeight, float yValue)
{
	Terrain* newModel = new Terrain(heightMap, texture, U, V, length, maxHeight, yValue);

	findName(name);
	modelMap[name] = newModel;
}

Terrain* TerrainManager::privGet(std::string name)
{
	auto it = modelMap.find(name);

	//Checks if the name already exists in the string 
	if (it == modelMap.end())
	{
		std::string message = "\n!!!!\nCannot find the name: " + name + "\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	return it->second;
}

Terrain* TerrainManager::privGet(DefaultTerrain ModelType)
{

	switch (ModelType)
	{
	case DefaultTerrain::FlatTerrain:
		return modelMap.find("Flat")->second;
	default:
		return modelMap.find("Flat")->second;
	}
}

void TerrainManager::Terminate()
{
	// Delete the pointer to the dynamically allocated object
	for (auto const& deleteMe : modelMap) {
		delete deleteMe.second;
	}
	modelMap.clear();

	//Deleting Instance for the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}

//Checks if the requested name already exists
void TerrainManager::findName(std::string name)
{
	if (modelMap.find(name) != modelMap.end())
	{
		std::string message = "\n!!!!\nThe name " + name + " has already been used. Please pick a new name \n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This name has already been used, check output for more details");
	}
}

void TerrainManager::privLoadDefaultResources()
{
	Terrain* pModelSprite = new Terrain(TextureManager::Get(TextureManager::DefaultTextures::PolliwogTextTexture), TextureManager::Get(TextureManager::DefaultTextures::PolliwogTextTexture));
	modelMap["Flat"] = pModelSprite;
}
