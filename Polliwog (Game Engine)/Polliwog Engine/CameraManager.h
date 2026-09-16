#include "../../src/Camera.h"
#include <map>

#pragma once

#ifndef _CameraManager
#define _CameraManager

class CameraManager
{
private:

	//Attributes
	Camera* activeCamera;
	Camera* defaultCamera;

	Camera* pCam2D;

	const std::string defaultCamPath = "DefaultCam"; //Default path
	const Vect defaultCameraUp = Vect(0.0f, 1.0f, 0.0f); //The 'Up' Camera Vector defines what direction is the top of the screen... I'm assuming the user will always want this facing upwards
	Vect lookAt3DCam = Vect(0.0f, 0.0f, 0.0f);
	Vect pos3DCam = Vect(50.0f, 50.0f, 150.0f);

public:

	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager();

	Camera* getCurrentCamera();
	Vect getCurrentPostion();

	void setCamera(Camera* c);
	void resetCamera();
	void updateCam(Matrix Rot, Vect Pos);
	void updateCam(Vect Rot, Vect Pos);

	Camera* get2D();

	void setLook(Vect l);
};

#endif _CameraManager
