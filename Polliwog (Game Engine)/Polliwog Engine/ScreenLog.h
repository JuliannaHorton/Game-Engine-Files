#pragma once

#ifndef _ScreenLog
#define _ScreenLog

//#include "Sprite.h"
#include <xmllite.h>
#include <vector>

class SpriteFont;
class SpriteString;
class ShowLog;

class ScreenLog
{
friend class ScreenLogAttorney;
private:

	static ScreenLog* ptrInstance;

	/// <summary>
	/// \ingroup FONT
	///	
	/// The sprite class exists to allows users to add 2D textures to the screen. 
	/// This might include a HUD, Gun Site, icons, ect.
	/// <br>
	/// <br>
	/// You can use the ScreenLog by simply placing it in Update
	/// \code
	/// void Tank::Update()
	/// {
	///	...
	///	ScreenLog::Add("\t\t\t\t\t\t\tFrigate: %3.1f, %3.1f, %3.1f", Pos.X(), Pos.Y(), Pos.Z());
	/// ...
	/// }
	/// \endcode
	/// <br>
	/// </summary>
	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;
	~ScreenLog() = default;

	static ScreenLog& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ScreenLog();
		return *ptrInstance;
	};

	void privRender();
	void privSetPos(int x, int y);
	static void Render() { Instance().privRender(); };
	static void Terminate();

	int anchorX = 50;
	int anchorY = 500;

	static char DebugBuff[256];
	static ShowLog* myLog;
	SpriteFont* font;

	using messagesCollection = std::vector<std::string>;
	messagesCollection Messages;

public:

	static void Add(const char* A, ...);
	static void Switch();
	static void SetPos(int x, int y) {Instance().privSetPos(x, y); };

};


#endif _ScreenLog