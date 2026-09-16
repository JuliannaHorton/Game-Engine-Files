#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "SpriteFont.h"


SpriteFontManager* SpriteFontManager::ptrInstance;
std::map<std::string, SpriteFont*> SpriteFontManager::FontList;


SpriteFont* SpriteFontManager::privGet(const std::string& name)
{
	auto it = FontList.find(name);

	if (it == FontList.end())
	{
		std::string message = "\n!!!!\nCannot find the name: " + name + "\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	return it->second;
}

SpriteFont* SpriteFontManager::privGet(DefaultFonts fontType)
{
	switch (fontType)
	{
	case DefaultFonts::PolliwogBasicFontWhite:
		return FontList.find("polliwogBasicFontWhite")->second;
	case DefaultFonts::PolliwogBasicFontBlack:
		return FontList.find("polliwogBasicFontBlack")->second;
	case DefaultFonts::PolliwogArialFontBlack:
		return FontList.find("ArialFontBlack")->second;
	case DefaultFonts::PolliwogPencilFont:
		return FontList.find("polliwogPencilFont")->second;
	case DefaultFonts::TankFont:
		return FontList.find("tankFont")->second;
	default:
		return FontList.find("polliwogBasicFontBlack")->second;
	}
}

void SpriteFontManager::privLoad(const std::string& key, const std::wstring& path)
{
	//std::string truePath = Defaultpath + path;
	SpriteFont* pFont = new SpriteFont(path);

	findName(key);
	FontList[key] = pFont;
}

void SpriteFontManager::privLoadDefaultResources()
{
	SpriteFont* basicFontW = new SpriteFont(L"BasicWhite");
	FontList["polliwogBasicFontWhite"] = basicFontW;

	SpriteFont* basicFontB = new SpriteFont(L"BasicBlack");
	FontList["polliwogBasicFontBlack"] = basicFontB;

	SpriteFont* ArialFontB = new SpriteFont(L"ArialFontBlack");
	FontList["ArialFontBlack"] = ArialFontB;

	SpriteFont* pencilFont = new SpriteFont(L"Test1");
	FontList["polliwogPencilFont"] = pencilFont;

	SpriteFont* tank = new SpriteFont(L"TankFont");
	FontList["tankFont"] = tank;
}


void SpriteFontManager::findName(std::string name)
{
	if (FontList.find(name) != FontList.end())
	{
		std::string message = "\n!!!!\nThe name " + name + " has already been used. Please pick a new name \n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This name has already been used, check output for more details");
	}
}

void SpriteFontManager::Terminate()
{
	for (auto const& deleteMe : FontList) {
		delete deleteMe.second;
	}
	FontList.clear();

	delete ptrInstance;
	ptrInstance = nullptr;
}