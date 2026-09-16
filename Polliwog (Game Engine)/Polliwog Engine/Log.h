#pragma once

#ifndef _Log
#define _Log

#include "ShowLog.h"
#include <vector>

class NoLog;
class RenderLog;

class Log
{
private:

public:
	static NoLog Null;
	static RenderLog Action;

};

#endif _Log