// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _Tadpole
#define _Tadpole

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include "../Finalsprint/Engine.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"

class Model;
class SkyBox;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class ShaderTexture;
class GraphicObject_Texture;
class ShaderColorLight;
class GraphicObject_Light;
class ShaderTextureLight;
class GraphicObject_TextureLight;
class GraphicObject_TextureFlat;
class GraphicObject_TextureLightFlat;
class GraphicObject_Sprite;
class GraphicObject_WireFrame;
class FireFlyShader;
class Image;
class SpriteShader;
class Sprite;
class CameraManager;

class Tadpole : public Engine, public Align16
{
friend class TadpoleAttorney;

private:	
	static Tadpole* ptrInstance;

/// <Summary>
/// \ingroup SETUP
/// 
/// <br>
/// The First step in your project will be loading in Assets, programming a few GameObjects, and creating your first Scene.
/// <br>
/// In Polliwog Resources there will be a LoadResources file that you will use to load in every file
/// required for your project. 
/// <br>
/// <br>
/// For Example your LoadResources may look like this to start:
/// /Code
/// void Polliwog::LoadResources()
/// {
///		SceneManager::setNextScene(new First Scene());
/// 
///		ModelManager::Load("ModelFrigate", "space_frigate.azul");
///		ModelManager::Load("Cottage", "Cottage.azul");
/// 
///		TextureManager::Load("FrigateTex", "space_frigate.tga");
///		TextureManager::Load("CottageTex", "Cottage.tga");
/// 
///		ShaderManager::Load("color", "colorConstantRender");
/// }
/// /endCode
/// <br>
/// Once you have your Assets loaded you can begin designing your Game Objects.
/// <br>
/// Here is a Basic Contructor of the space ship
/// \code
/// Frigate::Frigate()
///{
///		SpaceShip = new GraphicsObject_TextureFlat(ModelManager::Get("ModelFrigate"), ShaderManager::Get(ShaderManager::DefaultShaders::FlatRender), TextureManager::Get("FrigateTex"));
///
///		ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
///		ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 0);
///		World = ShipScale * ShipRotTrans;
///		SpaceShip->SetWorld(World);
///
///		Updatable::SubmitUpdateRegistration();
///		Drawable::SubmitDrawRegistration();
///
///		Inputable::SubmitRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::Key_Press);
///
///		SetColliderModel(SpaceShip->getModel());
///
///
///		SetCollidableGroup<Frigate>();
///		Collidable::SubmitCollisionRegistration();
///}
/// \endcode
/// 
/// \note This examples is using many commands involving registration and collision. Please go here \ref FEATURES "Important Polliwog Features"
/// for more details on how to use those methods
/// 
/// <br>
/// With your first Game Object created you can now add it to your FirstScene. Setting up your scene to start simply involves adding it to your Scene's Initialize methid
/// (Don't forget to delete in the deconstructor!)
/// 
/// \code
/// void TankScene::Intialize()
/// {
/// 	myTank = new Tank();
/// }
/// \endcode
/// <Summary>
/// 
	Tadpole() = default;
	Tadpole(const Tadpole&) = delete;
	Tadpole& operator=(const Tadpole&) = delete;
	~Tadpole() = default;

	static Tadpole& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new Tadpole();
		return *ptrInstance;
	};

	static void Terminate();

	virtual void LoadContent();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	virtual void OnMouseDown(WPARAM btnState, int xval, int yval);

	void LoadResources();
	void GameInitialize();
	void GameEnd();


	const char* name = "Polliwog";
	Vect WindowColor;

	//
// Window preferences
//
	void privSetWindowName(const char* windowName);
	void privSetWindowSize(int width, int height);
	void privSetWindowColor(Vect color);
	void privSetWindowColor(float red, float green, float blue, float opacity);

	int privGetHeight();
	int privGetWidth();
	const char* privGetWindowName();
	Vect privGetWindowColor();

	//
	// Game Time
	//
	static float GetTime();

public:

	static void funRun() { Instance().run(); Tadpole::Terminate(); };
	static void setWindow(HINSTANCE hInstance, int nCmdShow) { Instance().SetWindow(hInstance, nCmdShow); };
	static Tadpole& GetInstance();

	/// <summary>
	/// \defgroup WINDOW window control
	/// \ingroup POLLIWOG
	/// 
	/// Allows for control over the game window
	/// </summary>
	/// <param name="name"></param>	
	/// <summary>
	/// \ingroup WINDOW
	/// \brief Allows for the window name to be changed
	/// </summary>
	/// <param name="name"></param>
	static void SetWindowName(const char* name) { Instance().privSetWindowName(name); };
	/// <summary>
	/// \ingroup WINDOW
	/// \brief Allows for the window size to be changed
	/// </summary>
	/// <param name="name"></param>
	static void SetWindowSize(int width, int height) { Instance().privSetWindowSize(width, height); };
	/// <summary>
	/// \ingroup WINDOW
	/// \brief Allows for the window color to be changed
	/// </summary>
	/// <param name="name"></param>
	static void SetWindowColor(Vect color) { Instance().privSetWindowColor(color); };
	static void SetWindowColor(float red, float green, float blue, float opacity) { Instance().privSetWindowColor(red, green, blue, opacity); };

	/// <summary>
	/// \ingroup GET
	/// \brief Returns the height of the window
	/// </summary>
	/// <param name="name"></param>
	static int GetHeight() { return Instance().privGetHeight(); };

	/// <summary>
	/// \ingroup GET
	/// \brief Returns the width of the window
	/// </summary>
	/// <param name="name"></param>
	static int GetWidth() { return Instance().privGetWidth(); };
	/// <summary>
	/// \ingroup GET
	/// \brief Returns the name of the window
	/// </summary>
	/// <param name="name"></param>
	static const char* GetName() { return Instance().privGetWindowName(); };
	/// <summary>
	/// \ingroup GET
	/// \brief Returns the window color
	/// </summary>
	/// <param name="name"></param>
	static Vect GetWindowColor() { return Instance().privGetWindowColor(); };

};

#endif _Tadpole