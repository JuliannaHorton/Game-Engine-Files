#pragma once

#ifndef _SceneChangeNull
#define _SceneChangeNull

#include "SceneChange.h"

class SceneChangeNull : public SceneChange
{
public:
	SceneChangeNull() = default;
	SceneChangeNull(const SceneChangeNull&) = delete;
	SceneChangeNull& operator=(const SceneChangeNull&) = delete;
	~SceneChangeNull() = default;

	virtual void Action() override { ptrScene = nullptr; };
};

#endif _SceneChangeNull