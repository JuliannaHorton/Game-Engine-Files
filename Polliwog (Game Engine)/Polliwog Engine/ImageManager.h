#pragma once

#ifndef _ImageManager
#define _ImageManager

#include "Sprite.h"
#include <map>

class Image;
class Texture;

class ImageManager
{
	friend class ImageAttorney;
private:

	static ImageManager* ptrInstance;

	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ImageManager();
		return *ptrInstance;
	};

	using TimeLineMap = std::map<std::string, Image*>; //Stores our sprites
	static TimeLineMap spriteList;

	Image* privGet(const std::string&);
	void privLoad(const std::string&, Texture* tex);
	void privLoad(const std::string&, Texture* tex, RECT r);

	void findName(std::string name); //Just checks if the name has already been used

	static void Terminate();

public:

	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Images, based on a name and texture put into the parameters
	/// 
	/// \note Images are used for 2D objects, such as sprites, so in the actual game you will 
	///  need to use Draw2D for rendering
	/// </summary>
	/// <param name="name"></param>
	static void Load(const std::string& s, Texture* tex) { Instance().privLoad(s, tex); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Saves and allows access to your Images, based on a name, texture, and rectangle size put into the parameters
	/// 
	/// \note Images are used for 2D objects, such as sprites, so in the actual game you will 
	///  need to use Draw2D for rendering
	/// </summary>
	/// <param name="name"></param>
	static void Load(const std::string& s, Texture* tex, RECT r) { Instance().privLoad(s, tex, r); };
	/// <summary>
	/// \ingroup ASSETMANAGMENT
	/// \brief Returns the requested Image
	/// </summary>
	/// <param name="name"></param>
	static Image* Get(const std::string& s) { return Instance().privGet(s); };

};


#endif _ImageManager