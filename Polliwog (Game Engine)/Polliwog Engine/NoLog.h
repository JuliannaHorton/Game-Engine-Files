#pragma once

#ifndef _NoLog
#define _NoLog

#include "ShowLog.h"
class SpriteString;

class NoLog : public ShowLog
{
public:
	NoLog() = default;
	NoLog(const NoLog&) = delete;
	NoLog& operator=(const NoLog&) = delete;
	~NoLog() = default;

	virtual void Render(const std::vector<std::string>& Messages, int x, int y) { Messages, x, y; };
};

#endif _NoLog