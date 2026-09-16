#include "CameraManager.h"
#include "Tadpole.h"

CameraManager::CameraManager()
{
	defaultCamera = new Camera();
	//defaultCamera->setViewport(0, 0, Tadpole::GetWidth(), Tadpole::GetHeight());
	//defaultCamera->setPerspective(35.0f, Tadpole::GetWidth() / Tadpole::GetHeight(), 1.0f, 5000.0f);

	//// Orient Camera
	//defaultCamera->setOrientAndPosition(defaultCameraUp, lookAt3DCam, pos3DCam);
	//defaultCamera->updateCamera();

	defaultCamera->setPerspective(3.14159 / 3, (float)Tadpole::GetWidth() / (float)(Tadpole::GetHeight()), 1.0f, 7000.0f); //Why is the height slightly off?
	defaultCamera->setOrthographic(0.0f, (float)Tadpole::GetWidth(), 0.0f, (float)Tadpole::GetHeight(), -1.0f, 1000.0f);
	defaultCamera->setOrientAndPosition(defaultCameraUp, Vect(123.12f, 37.88f, -63.55f), Vect(124, 38, -64));

	activeCamera = defaultCamera;

	defaultCamera->updateCamera();

	pCam2D = new Camera();
	pCam2D->setPerspective(3.14159 / 3, (float)Tadpole::GetWidth() / (float)(Tadpole::GetHeight()), 1.0f, 5000.0f);
	pCam2D->setOrthographic(0.0f, (float)Tadpole::GetWidth(), 0.0f, (float)(Tadpole::GetHeight()), -1.0f, 1000.0f);
	pCam2D->setOrientAndPosition(defaultCameraUp, Vect(123.12f, 37.88f, -63.55f), Vect(124, 38, -64));

	// Orient Camera
	//Vect up2DCam(0.0f, 1.0f, 0.0f);
	//Vect pos2DCam(0.0f, 0.0f, 0.0f);
	//Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	//pCam2D->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	//pCam2D->updateCamera();

}

CameraManager::~CameraManager()
{
	delete defaultCamera;
	delete pCam2D;
}

void CameraManager::updateCam(Matrix Rot, Vect Pos)
{
	//pos3DCam = Pos;
	//activeCamera->setOrientAndPosition(defaultCameraUp, lookAt3DCam * Rot, Pos); //This is fine
	activeCamera->updateCamera();
}

void CameraManager::updateCam(Vect Rot, Vect Pos)
{
	//pos3DCam = Pos;
	//activeCamera->setOrientAndPosition(defaultCameraUp, Rot, Pos); //This is fine
	defaultCamera->updateCamera();
}

void CameraManager::setCamera(Camera* c)
{
	activeCamera = c;
}

void CameraManager::resetCamera()
{
	activeCamera = defaultCamera;
}

Camera* CameraManager::getCurrentCamera() //for right now I just have one camera
{
	return activeCamera;
}

Vect CameraManager::getCurrentPostion()
{
	return pos3DCam;
}

void CameraManager::setLook(Vect c)
{
	//lookAt3DCam = c;
}

Camera* CameraManager::get2D()
{
	return defaultCamera;
}
