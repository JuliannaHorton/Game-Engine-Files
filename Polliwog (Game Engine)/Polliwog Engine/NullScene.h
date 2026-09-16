#pragma once

#ifndef _SceneNull
#define _SceneNull

#include "Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator=(const SceneNull&) = delete;
	~SceneNull() = default;

	virtual void Intialize() {};
	virtual void SceneEnd() {};

};


#endif _SceneNull