#include "TextureManager.h"
#include "../../src/Texture.h"

TextureManager* TextureManager::ptrInstance = nullptr;
std::map<std::string, Texture*> TextureManager::textureMap;

//
// wString: Same as regular string but requires more than one byte per a character, with w standing for "wide"
//			Its good for supporting large character sets, such as characters from other languages... so don't exactly need them, but they'll be fine
//

void TextureManager::privLoad(std::string name, std::wstring shader)
{
	std::wstring truePath = defaultPath + shader;
	Texture* newTexture = new Texture(truePath.c_str());

	testName(name);
	textureMap[name] = newTexture;


}

void TextureManager::privLoad(std::string name, Vect Color)
{
	//
	// NOTE TO SELF: I forgot about this wierd color texture type and didn't finish it... ADD ASAP
	// 

	//Texture* newTexture = new Texture(Color);

	//textureMap[name] = newTexture;
}

Texture* TextureManager::privGet(std::string name)
{
	auto it = textureMap.find(name);

	if (it == textureMap.end())
	{
		std::string message = "\n!!!!\nCannot find the name: " + name + "\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	return it->second;
}

Texture* TextureManager::privGet(DefaultTextures textureType)
{
	switch (textureType)
	{
	case DefaultTextures::PolliwogTextTexture:
		return textureMap.find("TextTexture")->second;
	default:
		return textureMap.find("TextTexture")->second;
	}
}

void TextureManager::privLoadDefaultResources()
{
	//Texture* text = new Texture("Textures/grid.tga");
	//textureMap["TextTexture"] = text;
}

void TextureManager::Terminate()
{
	// Delete the pointer to the dynamically allocated object
	for (auto const& deleteMe : textureMap) {
		delete deleteMe.second;
	}
	textureMap.clear();

	//Deleting Instance for the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}



void TextureManager::testName(std::string name)
{
	if (textureMap.find(name) != textureMap.end())
	{
		std::string message = "\n!!!!\nThe name " + name + " has already been used. Please pick a new name \n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This name has already been used, check output for more details"); //Is it better to throw an error?
	}
}