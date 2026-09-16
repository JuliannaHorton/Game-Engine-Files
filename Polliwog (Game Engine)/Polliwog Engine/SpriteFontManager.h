#pragma once

#ifndef _SpriteFontManager
#define _SpriteFontManager

#include "Sprite.h"
#include <map>

class SpriteFont;
class Texture;

class SpriteFontManager
{
	friend class FontManAttorney;
public:
	enum class DefaultFonts
	{
		PolliwogBasicFontBlack,
		PolliwogBasicFontWhite,
		PolliwogArialFontBlack,
		PolliwogPencilFont,
		TankFont
	};

	void privLoadDefaultResources();
	static void LoadDefaultResources() { Instance().privLoadDefaultResources(); };
private:

	static SpriteFontManager* ptrInstance;

	SpriteFontManager() = default;
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new SpriteFontManager();
		return *ptrInstance;
	};

	std::string Defaultpath = "../Assets/Fonts/";

	using TimeLineMap = std::map<std::string, SpriteFont*>; //Stores our sprites
	static TimeLineMap FontList;

	SpriteFont* privGet(const std::string& key);
	SpriteFont* privGet(DefaultFonts);
	void privLoad(const std::string& key, const std::wstring& path);

	void findName(std::string name);

	static void Terminate();

public:

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Fonts
	/// </summary>
	/// <param name="name"></param>
	static void Load(const std::string& key, const std::wstring& path) { Instance().privLoad(key, path); };

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Font
	/// </summary>
	/// <param name="name"></param>
	static SpriteFont* Get(const std::string& key) { return Instance().privGet(key); };
	static SpriteFont* Get(DefaultFonts key) { return Instance().privGet(key); };

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Preloads default Fonts
	/// </summary>
	/// 
	/// You'll want to add this method in 'LoadResources.cpp'
	/// \code
	/// void Polliwog::LoadResources()
	///{
	///	SpriteFontManager::LoadDefaultResources();
	/// ...
	///}
	/// \endcode
	/// <param name="name"></param>

};


#endif _SpriteFontManager