#pragma once

#ifndef _SceneChangeAction
#define _SceneChangeAction

#include "SceneChange.h"

class SceneChangeAction : public SceneChange
{
public:
	SceneChangeAction() = default;
	SceneChangeAction(const SceneChangeAction&) = delete;
	SceneChangeAction& operator=(const SceneChangeAction&) = delete;
	~SceneChangeAction() = default;

	virtual void Action();
};

#endif _SceneChangeAction