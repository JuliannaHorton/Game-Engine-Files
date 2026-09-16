// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include <string>
#include <xmllite.h>
#include <map>

#include <xmllite.h>
#include <shlwapi.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "../Polliwog Engine/Sprite.h"
class Texture;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = Sprite;

private:
	std::string Name;
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

	std::wstring FontName;

public:
	SpriteFont() = delete;
	SpriteFont(std::wstring path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	Glyph* GetGlyph(char c);
};

#endif _SpriteFont