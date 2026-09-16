#pragma once
#pragma once

#ifndef _TextureManager
#define _TextureManager

#include <map>
#include <Vect.h>
#include <string>

class Texture;
class Vect;

class TextureManager
{
	friend class AssetAttorney;

public:
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Default Polliwog Shaders
	/// </summary>
	/// <param name="name"></param>
	enum class DefaultTextures
	{
		PolliwogTextTexture,
	};

private:
	//Singleton
	static TextureManager* ptrInstance;

	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager() = default;

	static TextureManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new TextureManager();
		return *ptrInstance;
	};

	static void Terminate();

	//
	// Methods for loading and getting Assets
	//
	void privLoad(std::string, std::wstring); //key, name, renderfile
	void privLoad(std::string, Vect Color); //key, name, renderfile
	Texture* privGet(std::string name);
	Texture* privGet(DefaultTextures);
	static void privLoadDefaultResources();
	static void LoadDefaultResources() { Instance().privLoadDefaultResources(); };

	//
	// Data Structure: HashTable --- Stores loaded Models with a key string
	//
	static std::map<std::string, Texture*> textureMap;
	const std::wstring defaultPath = L"../Assets/Textures/";

	void testName(std::string name); //Switch to main Asset Manager later

public:

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Textures, based on the name and filepath specified by the parameters
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, std::wstring texturePath) { Instance().privLoad(name, texturePath); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Textures, based on the name and color specified by the parameters
	/// </summary>
	/// <param name="name"></param>
	static void Load(std::string name, Vect c) { Instance().privLoad(name, c); };

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Texture
	/// </summary>
	/// <param name="name"></param>
	static Texture* Get(std::string name) { return Instance().privGet(name); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Default Texture
	/// </summary>
	/// <param name="name"></param>
	static Texture* Get(DefaultTextures textureType) { return Instance().privGet(textureType); };

};

#endif _ShaderManager