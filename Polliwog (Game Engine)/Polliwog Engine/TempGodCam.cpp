#include "TempGodCam.h"
#include "../Polliwog Engine/CameraManager.h"
#include "../Polliwog Engine/ImageManager.h"

#include "../Polliwog Engine/SceneManager.h"
#include "../Polliwog Engine/ScreenLog.h"

#include "../Polliwog Engine/Sprite.h"
#include "../Polliwog Engine/SpriteString.h"
#include "../Polliwog Engine/SpriteFontManager.h"

TempGodCam::TempGodCam(Camera* pCamMan)
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

	heart = new Sprite("Heart");
	heart->SetPosition(100, 900);

	bullet = new Sprite("Bullet");
	bullet->SetPosition(900, 900);

	heart2 = new Sprite("Heart");
	heart2->SetPosition(200, 900);

	bullet2 = new Sprite("Bullet");
	bullet2->SetPosition(900, 720);

	heart3 = new Sprite("Heart");
	heart3->SetPosition(300, 900);

	bullet3 = new Sprite("Bullet");
	bullet3->SetPosition(900, 540);

	heart4 = new Sprite("Heart");
	heart4->SetPosition(400, 900);

	bullet4 = new Sprite("Bullet");
	bullet4->SetPosition(900, 360);


	font = new SpriteString(SpriteFontManager::Get(SpriteFontManager::DefaultFonts::TankFont), "SCORE: ", 50, 700);
	font->SetSize(10, 10);
}

TempGodCam::~TempGodCam()
{
	delete heart;
	delete bullet;
	delete font;
	delete heart2;
	delete bullet2;
	delete heart3;
	delete bullet3;
	delete heart4;
	delete bullet4;

}

void TempGodCam::SceneEntry() {
	SubmitUpdateRegistration();

	CamRot = Matrix(IDENTITY);
	CamDir = Vect(0.0f, 0.0f, 1.0f);

	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	camMan->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	camMan->updateCamera();
}

void TempGodCam::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();

	SubmitDeregistration(FROG_KEY::KEY_Q, EVENT_TYPE::Key_Press);
}

void TempGodCam::Draw2D()
{
	//heart->Render(camMan);
	//bullet->Render(camMan);
	//font->Render(camMan);

	//heart2->Render(camMan);
	//bullet2->Render(camMan);

	//heart3->Render(camMan);
	//bullet3->Render(camMan);

	//heart4->Render(camMan);
	//bullet4->Render(camMan);
}

void TempGodCam::Update()
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
	ScreenLog::Add("\t\t\CamPos: %3.1f, %3.1f, %3.1f", Pos.X(), Pos.Y(), Pos.Z());
	camMan->updateCamera();
}
