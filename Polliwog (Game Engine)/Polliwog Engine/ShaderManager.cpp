#include "ShaderManager.h"
#include "../../src/ShaderBase.h"
#include "../SpriteShader.h"
#include "../ShaderTexture.h"
#include "../ShaderTextureLight.h"
#include "../../src/ShaderColor.h"
#include "../../src/ShaderColorLight.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;
std::map<std::string, ShaderBase*> ShaderManager::shaderMap;

void ShaderManager::privLoad(std::string name, std::wstring shader)
{
	//std::wstring truePath = defaultPath + shader;
	//ShaderBase* newShader = new ShaderBase(truePath.c_str());

	//testName(name);
	//shaderMap[name] = newShader;
}

ShaderBase* ShaderManager::privGet(std::string name)
{
	auto it = shaderMap.find(name);

	if (it == shaderMap.end())
	{
		std::string message = "\n!!!!\nCannot find the name: " + name + "\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	return it->second;
}

ShaderBase* ShaderManager::privGet(DefaultShaders shaderType)
{
	switch (shaderType)
	{
	case DefaultShaders::PolliwogTexturetRender:
		return shaderMap.find("DefaultFlat")->second;
	case DefaultShaders::PolliwogTextureLightRender:
		return shaderMap.find("LighRender")->second;
	case DefaultShaders::PolliwogColorRender:
		return shaderMap.find("ColorRender")->second;
	case DefaultShaders::PolliwogColorLightRender:
		return shaderMap.find("ColorLightRender")->second;
	case DefaultShaders::PolliwogSpriteRender:
		return shaderMap.find("SpriteRender")->second;
	default:
		return shaderMap.find("ColorRender")->second;
	}
}

void ShaderManager::privLoadDefaultResources()
{
	ShaderTexture* flatShader = new ShaderTexture();
	shaderMap["DefaultFlat"] = flatShader;

	ShaderTextureLight* lightShader = new ShaderTextureLight();
	shaderMap["LighRender"] = lightShader;

	ShaderColor* colorShader = new ShaderColor();
	shaderMap["ColorRender"] = colorShader;

	ShaderColorLight* colorLightShader = new ShaderColorLight();
	shaderMap["ColorLightRender"] = colorLightShader;

	SpriteShader* spriteShader = new SpriteShader();
	shaderMap["SpriteRender"] = spriteShader;
}

void ShaderManager::Terminate()
{
	// Delete the pointer to the dynamically allocated object
	for (auto const& deleteMe : shaderMap) {
		delete deleteMe.second;
	}
	shaderMap.clear();

	//Deleting Instance for the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}



void ShaderManager::testName(std::string name)
{
	if (shaderMap.find(name) != shaderMap.end())
	{
		std::string message = "\n!!!!\nThe name " + name + " has already been used. Please pick a new name \n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This name has already been used, check output for more details"); //Is it better to throw an error?
	}
}