#pragma once

#ifndef _ShowLog
#define _ShowLog

#include <vector>
class SpriteString;

class ShowLog
{
public:
	ShowLog() = default;
	ShowLog(const ShowLog&) = delete;
	ShowLog& operator=(const ShowLog&) = delete;
	virtual ~ShowLog() = default;

	virtual void Render(const std::vector<std::string>& Messages, int x, int y) = 0;
};

#endif _ShowLog