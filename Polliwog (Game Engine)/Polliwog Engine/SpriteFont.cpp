#pragma comment(lib, "XmlLite.lib")
#pragma comment(lib, "Shlwapi.lib")

#include "SpriteFont.h"
#include "TextureManager.h"
#include "ImageManager.h"

//*********************************************************
// Don't forget to add the associated libs to your project 
// Properties/Linker/Input  -> add these
//		xmllite.lib
//		shlwapi.lib
//*********************************************************

//Converter
std::string ws2s(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

SpriteFont::SpriteFont(std::wstring path) //Maybe I make this two paths: one for xml and another for tga
{
	// <Load associated texture into TextureManager>

	FontName = path;
	TextureManager::Load(ws2s(path), path + L".tga");

	// Parse associated XML file
	XMLtoCollection("../Assets/Fonts/" + ws2s(path) + ".xml");
}

SpriteFont::~SpriteFont()
{
	for (auto const& deleteMe : fontmap) {
		delete deleteMe.second;
	}
	fontmap.clear();
}

void SpriteFont::XMLtoCollection(std::string filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;	// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				ElementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				ElementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				ElementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				ElementTextToInt(reader, h);
			}
			else
			{
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				//************************************************************************
				// You now have all the data for a character: key, x, y, w, h
				//
				// Load the associated image in the ImageManager 
				// (its name could be <font name><key> to insure uniqueness)
				//
				// Create the glyph and add it to the fontmap
				// NB: Consider moving the glyph's origin to the *upper-left* corner...
				//*************************************************************************

				//Convert the key into a character
				char charKey = (char)key;
				std::string mySpriteKey(1, charKey);

				//Push the character into the map with its associated value
				RECT Letter;
				Letter.left = (float)x;
				Letter.top = (float)y;
				Letter.right = (float)w;
				Letter.bottom = (float)h;
				ImageManager::Load(ws2s(FontName) + mySpriteKey, TextureManager::Get(ws2s(FontName)), Letter); //Set the position and size of each Character

				RECT spr;
				spr.left = 0;
				spr.top = 0;
				spr.right = w;
				spr.bottom = h;
				fontmap[key] = new Sprite(ws2s(FontName) + mySpriteKey, spr); //Create a new Sprite for each character
				fontmap[key]->SetCenter(w * 0.5f, h * 0.5f);

				//DebugMsg::out("Font %s: creating glyph for ASCII %i\n", Name.c_str(), key);
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	float spaceWidth = fontmap[(int)' ']->GetWidth();
	RECT l;
	l.left = 0;
	l.top = 0;
	l.right = (4 * spaceWidth);
	l.bottom = 1;

	ImageManager::Load(ws2s(FontName) + '\t', TextureManager::Get(ws2s(FontName)), l); //Set the position and size of each Character
	fontmap[9] = new Sprite(ws2s(FontName) + '\t', l); //Create a new Sprite for each character

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
}

void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c)
{
	return fontmap[(int)c];
}


