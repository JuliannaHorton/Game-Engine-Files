#pragma once

#ifndef _ModelManager
#define _ModelManager

#include "../../src/Model.h"
#include <map>

class ModelManager
{
	friend class AssetAttorney;

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Default Polliwog Models
	/// </summary>
	/// <param name="name"></param>
	enum class DefaultModels
	{
		PolliwogSpriteModel,
		TerrainModel
	};
private:
	static ModelManager* ptrInstance;

	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager() = default;

	static ModelManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ModelManager();
		return *ptrInstance;
	};

	//
	// Methods for loading and Getting Assets
	//
	void privLoad(std::string, int, int, int); //name, specifications
	void privLoad(std::string, std::string); //name, key
	void privLoad(std::string, Model::PreMadeModels model_type); //name, key
	Model* privGet(std::string name);
	Model* privGet(DefaultModels ModelType);

	void privLoadDefaultResources();

	//
	// Data Structure: HashTable --- Stores loaded Models with a key string
	//
	static std::map<std::string, Model*> modelMap;
	const std::string defaultPath = "../Assets/Models/";

	static void Terminate();

	void findName(std::string name);
	static void LoadDefaultResources() { Instance().privLoadDefaultResources(); };

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your models, based on the specified name and filepath in the parameters
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, std::string modelPath) { Instance().privLoad(name, modelPath); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your models, based on the specified name, size, and UVs in the parameters
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, int planesize, int u, int v) { Instance().privLoad(name, planesize, u, v); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your models, based on the specified name and selected pre-made model (such as sphere and pyramid) in the parameters
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, Model::PreMadeModels modelType) { Instance().privLoad(name, modelType); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Model
	/// </summary>
	/// <param name="name"></param>
	static Model* Get(std::string name) { return Instance().privGet(name); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Default Model
	/// </summary>
	/// <param name="name"></param>
	static Model* Get(DefaultModels ModelType) { return Instance().privGet(ModelType); };
};

#endif _ShaderManager