#include "GodCam.h"
#include "../Polliwog Engine/CameraManager.h"
#include "../Polliwog Engine/ImageManager.h"

#include "../Polliwog Engine/SceneManager.h"
#include "../Polliwog Engine/ScreenLog.h"

#include "../Polliwog Engine/Sprite.h"
#include "../Polliwog Engine/SpriteString.h"
#include "../Polliwog Engine/SpriteFontManager.h"

GodCam::GodCam(Camera* pCamMan)
{
	CamRot = Matrix(IDENTITY);
	CamDir = Vect(0.0f, 0.0f, 1.0f);

	camMan = pCamMan;

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	camMan->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	camMan->updateCamera();
}

void GodCam::SceneEntry() {
	SubmitUpdateRegistration();

	CamRot = Matrix(IDENTITY);
	CamDir = Vect(0.0f, 0.0f, 1.0f);

	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	camMan->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	camMan->updateCamera();
}

void GodCam::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();

	SubmitDeregistration(FROG_KEY::KEY_Q, EVENT_TYPE::Key_Press);
}

void GodCam::Update()
{
	float camSpeed = 1.5f;
	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_W))
	{
		camMan->TranslateFwdBack(camSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_S))
	{
		camMan->TranslateFwdBack(-camSpeed);
	}

	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_A))
	{
		camMan->TranslateLeftRight(-camSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_D))
	{
		camMan->TranslateLeftRight(camSpeed);
	}

	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_LEFT))
	{
		camMan->TurnLeftRight(CamRotSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_RIGHT))
	{
		camMan->TurnLeftRight(-CamRotSpeed);
	}

	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_UP))
	{
		camMan->TiltUpDown(CamRotSpeed);
	}
	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_ARROW_DOWN))
	{
		camMan->TiltUpDown(-CamRotSpeed);
	}

	Vect Pos;
	camMan->getPos(Pos);
	//ScreenLog::Add("\t\t\CamPos: %3.1f, %3.1f, %3.1f", Pos.X(), Pos.Y(), Pos.Z());
	camMan->updateCamera();
}
