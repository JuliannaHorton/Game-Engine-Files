#pragma once

#ifndef _SceneChange
#define _SceneChange

class Scene;

class SceneChange
{
public:
	SceneChange() = default;
	SceneChange(const SceneChange&) = delete;
	SceneChange& operator=(const SceneChange&) = delete;
	virtual ~SceneChange() = default;

	virtual void Action() = 0;

	void setScene(Scene* s) { ptrScene = s; };

protected:
	Scene* ptrScene = nullptr;
};

#endif _SceneChange