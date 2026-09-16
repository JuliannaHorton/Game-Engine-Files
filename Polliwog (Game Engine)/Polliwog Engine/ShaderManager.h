#pragma once

#ifndef _ShaderManager
#define _ShaderManager

#include <map>

class ShaderBase;

class ShaderManager
{
	friend class AssetAttorney;

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Default Polliwog Shaders
	/// </summary>
	/// <param name="name"></param>
	enum class DefaultShaders
	{
		PolliwogTexturetRender,
		PolliwogTextureLightRender,
		PolliwogSpriteRender,
		PolliwogColorRender,
		PolliwogColorLightRender
	};

private:
	//Singleton
	static ShaderManager* ptrInstance;

	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ShaderManager(); //WHY IS THIS REFERENCING A DELETED FUNCTION
		return *ptrInstance;
	};

	static void Terminate();

	//
	// Methods for loading and Getting Assets
	//
	void privLoad(std::string, std::wstring);
	ShaderBase* privGet(std::string);
	ShaderBase* privGet(DefaultShaders);
	void privLoadDefaultResources();
	static void LoadDefaultResources() { Instance().privLoadDefaultResources(); };

	//
	// Data Structure: HashTable --- Stores loaded Models with a key string
	//

	static std::map<std::string, ShaderBase*> shaderMap; //Map
	const std::wstring defaultPath = L"../Assets/Shaders/"; //Default path

	void testName(std::string name); //Switch to main Asset Manager later

	static ShaderBase* flatShader;

	static ShaderBase* lightShader;

	static ShaderBase* colorShader;

	static ShaderBase* colorLightShader;

	static ShaderBase* spriteShader;

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Shaders
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, std::wstring shaderPath) { Instance().privLoad(name, shaderPath); };

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Shader
	/// </summary>
	/// <param name="name"></param>
	static ShaderBase* Get(std::string name) { return Instance().privGet(name); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Default Shader
	/// </summary>
	/// <param name="name"></param>
	static ShaderBase* Get(DefaultShaders shaderType) { return Instance().privGet(shaderType); };

};

#endif _ShaderManager