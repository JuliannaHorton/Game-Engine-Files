#pragma once

#ifndef _GodCam
#define _GodCam

#include "../Polliwog Engine/GameObject.h"

class Camera;
class Sprite;
class SpriteString;

class TempGodCam : public GameObject
{
public:
	TempGodCam() = default;
	TempGodCam(const TempGodCam&) = delete;
	TempGodCam& operator=(const TempGodCam&) = delete;
	~TempGodCam();

	TempGodCam(Camera* camMan);

	virtual void Update();
	virtual void Draw2D();
	virtual void SceneEntry();
	virtual void SceneExit();

private:
	Vect CamPos = Vect(124, 38, -64);
	Vect CamUp = Vect(0.0f, 1.0f, 0.0f);
	Vect CamDir;
	Matrix CamRot;
	Matrix World;

	Camera* camMan;
	Sprite* heart;
	Sprite* bullet;
	SpriteString* font;
	Sprite* heart2;
	Sprite* bullet2;
	Sprite* heart3;
	Sprite* bullet3;
	Sprite* heart4;
	Sprite* bullet4;
	Sprite* heart5;
	Sprite* bullet5;

	const float CamSpeed = 1;
	const float CamRotSpeed = 0.01f;
};


#endif _GodCam