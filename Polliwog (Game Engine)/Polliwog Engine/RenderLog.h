#pragma once

#ifndef _RenderLog
#define _RenderLog

#include "ShowLog.h"
class SpriteString;

class RenderLog : public ShowLog
{
public:
	RenderLog() = default;
	RenderLog(const RenderLog&) = delete;
	RenderLog& operator=(const RenderLog&) = delete;
	~RenderLog() = default;

	virtual void Render(const std::vector<std::string>& Messages, int x, int y);
};

#endif _RenderLog