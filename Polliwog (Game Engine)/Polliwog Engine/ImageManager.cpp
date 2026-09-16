#include "ImageManager.h"

ImageManager* ImageManager::ptrInstance;
std::map<std::string, Image*> ImageManager::spriteList;


Image* ImageManager::privGet(const std::string& name)
{
	auto it = spriteList.find(name);

	if (it == spriteList.end())
	{
		std::string message = "\n!!!!\nCannot find the name: " + name + "\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	return it->second;
}

void ImageManager::privLoad(const std::string& name, Texture* tex)
{

	RECT Img;
	Img.top = 0;
	Img.left = 0;
	Img.bottom = tex->getHeight();
	Img.right = tex->getWidth();

	Image* pImageStitch = new Image(tex, Img);

	findName(name);
	spriteList[name] = pImageStitch;
}

void ImageManager::privLoad(const std::string& name, Texture* tex, RECT r)
{
	Image* pImageStitch = new Image(tex, r);

	findName(name);
	spriteList[name] = pImageStitch;
}

void ImageManager::findName(std::string name)
{
	if (spriteList.find(name) != spriteList.end())
	{
		std::string message = "\n!!!!\nThe name " + name + " has already been used. Please pick a new name \n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This name has already been used, check output for more details");
	}
}

void ImageManager::Terminate()
{
	for (auto const& deleteMe : spriteList) {
		delete deleteMe.second;
	}
	spriteList.clear();

	delete ptrInstance;
	ptrInstance = nullptr;
}