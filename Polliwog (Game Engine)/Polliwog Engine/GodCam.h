#pragma once

#ifndef _GodCam
#define _GodCam

#include "../Polliwog Engine/GameObject.h"

class Camera;
class Sprite;
class SpriteString;

class GodCam : public GameObject
{
public:
	GodCam() = default;
	GodCam(const GodCam&) = delete;
	GodCam& operator=(const GodCam&) = delete;
	~GodCam() = default;

	GodCam(Camera* camMan);

	virtual void Update();
	virtual void SceneEntry();
	virtual void SceneExit();

private:
	Vect CamPos = Vect(124, 38, -64);
	Vect CamUp = Vect(0.0f, 1.0f, 0.0f);
	Vect CamDir;
	Matrix CamRot;
	Matrix World;

	Camera* camMan;

	const float CamSpeed = 1;
	const float CamRotSpeed = 0.01f;
};


#endif _GodCam