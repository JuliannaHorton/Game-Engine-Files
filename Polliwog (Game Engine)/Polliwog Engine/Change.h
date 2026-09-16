#pragma once

#ifndef _Change
#define _Change

class SceneChangeAction;
class SceneChangeNull;

class Change
{
private:

public:
	static SceneChangeNull Null;
	static SceneChangeAction Action;

};

#endif _Change