#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteFont.h"
#include "SpriteString.h"
#include "Log.h"
#include "RenderLog.h"
#include "NoLog.h"

#include <stdarg.h>
#include <stdio.h>

ScreenLog* ScreenLog::ptrInstance = nullptr;
//std::vector<std::string> ScreenLog::Messages;
char ScreenLog::DebugBuff[256];
ShowLog* ScreenLog::myLog;

ScreenLog::ScreenLog()
{
	font = SpriteFontManager::Get(SpriteFontManager::DefaultFonts::PolliwogArialFontBlack);
	myLog = &Log::Action;
}

/// <summary>
/// \ingroup FONT
/// \brief Adds text to the ScreenLog
/// 
/// </summary>
void ScreenLog::Add(const char* A, ...)
{
	va_list args;

	va_start(args, A);
	vsnprintf_s(DebugBuff, sizeof(DebugBuff), _TRUNCATE, A, args);
	va_end(args);

	std::string s(DebugBuff);
	Instance().Messages.push_back(s);
}

void ScreenLog::privRender()
{
	myLog->Render(Messages, anchorX, anchorY);
	Messages.clear();
}

/// <summary>
/// \ingroup FONT
/// \brief Turns the ScreenLog off and on
/// 
/// </summary>
void ScreenLog::Switch()
{                        
	if (myLog == &Log::Action)
	{
		myLog = &Log::Null;
	}
	else
	{
		myLog = &Log::Action;
	}
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the position of the Log
/// 
/// </summary>
void ScreenLog::privSetPos(int x, int y)
{
	anchorX = x;
	anchorY = y;
}

void ScreenLog::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}