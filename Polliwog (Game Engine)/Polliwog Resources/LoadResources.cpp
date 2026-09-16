
#include "../Finalsprint/Polliwog Engine/Tadpole.h"
#include "../Polliwog Engine/AssetAttorney.h"

#include "../Polliwog Engine/ImageManager.h"
#include "../Polliwog Engine/SceneManager.h"

#include "../DirLightManager.h"
#include "../PointLightManager.h"
#include "../SpotLightManager.h"

#include "../Polliwog Engine/SpriteFontManager.h"

#include "../User Defined Code/SceneDemo.h"
#include "../User Defined Code/TerrainScene.h"
#include "../User Defined Code/CityScene.h"
#include "../User Defined Code/SplashScene.h"

void Tadpole::LoadResources()
{
	SceneManager::setNextScene(new SplashScene());

	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	// Tank models
	ModelManager::Load("TankHead", "TankTop1.azul");
	ModelManager::Load("TankGun", "TankGunPivot.azul");
	ModelManager::Load("ModelBox", "TankBottom.azul"); //idk why I named it modelBox

	// Turret Models
	ModelManager::Load("TurretBottom", "TurretBotBottom.azul");
	ModelManager::Load("TurretHead", "TurretHead.azul");
	ModelManager::Load("TurretStand", "TurretStand.azul");
	ModelManager::Load("StandingHead", "StandingTurretHead.azul");
	ModelManager::Load("FlyGuy", "FlyGuy.azul");

	// Building Models
	ModelManager::Load("Shop_A", "TwoStoryBuilding.azul");
	ModelManager::Load("Shop_B", "Shop_B.azul");
	ModelManager::Load("OneStory", "SmallBuilding.azul");
	ModelManager::Load("BigBuilding_A", "BigBuilding2.azul");
	ModelManager::Load("Shop_C", "CornerShop.azul");
	ModelManager::Load("Shop_C_Big", "CornerShop2x.azul");

	// Other
	ModelManager::Load("UFO", "UFO.azul");
	ModelManager::Load("beam", "Beam.azul");
	ModelManager::Load("Tunnel", "Tunnel.azul");


	ModelManager::Load("pModel1", "space_frigate.azul");
	ModelManager::Load("ModelSphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("Box", Model::PreMadeModels::UnitBoxSixFacesTexture);

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	// Tank Textures
	TextureManager::Load("TankBottom", L"TankBottomTex.tga");
	TextureManager::Load("TankHead", L"TankTop.tga");
	TextureManager::Load("TankGun", L"TankGunTex.tga");
	TextureManager::Load("Site", L"GunSite.tga");

	// Turret Textures
	TextureManager::Load("TurretBottomTex", L"TurretBottomTex.tga");
	TextureManager::Load("tHead", L"TurretHead.tga");
	TextureManager::Load("EvilTurret", L"TurretEvil.tga");
	TextureManager::Load("TurretBottom", L"TurretStand.tga");
	TextureManager::Load("TurretHeadTEx", L"StandingTurretHead.tga");
	TextureManager::Load("FlyGuyTex", L"FlyGuy.tga");

	// Building Textures
	TextureManager::Load("BigBuilding_A", L"BigBuilding.tga");
	TextureManager::Load("Shop_C", L"Shop_C.tga");
	TextureManager::Load("Shop_B", L"Shop_A.tga");
	TextureManager::Load("Shop_A", L"TwoStoryBuilding.tga");
	TextureManager::Load("OneStory", L"SmallBuilding.tga");
	TextureManager::Load("OneStoryRed", L"SmallBuildingRed.tga");

	// Other 
	TextureManager::Load("UFO", L"UFO.tga");
	TextureManager::Load("SkyBox", L"SkyBox.tga");
	TextureManager::Load("night", L"NightTime.tga");
	TextureManager::Load("beam", L"Beam.tga");
	TextureManager::Load("RoadMap", L"RoadMap.tga");

	TextureManager::Load("FrigateTex", L"space_frigate.tga");
	TextureManager::Load("GridTex", L"grid.tga");
	TextureManager::Load("Frog", L"HappyFrog.tga");
	TextureManager::Load("stitch", L"stitch.tga");

	TextureManager::Load("test", L"HMTest.tga");
	TextureManager::Load("Grass", L"GoodGrass.tga");

	TextureManager::Load("Heart", L"TankHeart.tga");
	TextureManager::Load("Bullet", L"TankBullet.tga");

	TextureManager::Load("Tunnel", L"Tunnel.tga");

	TextureManager::Load("Instructions", L"Instructions.tga");
	TextureManager::Load("StartMessage", L"StartMessage.tga");
	TextureManager::Load("FirstObjective", L"FirstObjective.tga");
	TextureManager::Load("SecondObjective", L"SecondObjective.tga");
	TextureManager::Load("landed", L"UFOLanded.tga");

	TextureManager::Load("won", L"Won.tga");
	TextureManager::Load("lost", L"Lost.tga");
	TextureManager::Load("restart", L"Restart.tga");
	TextureManager::Load("objective", L"Objective.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load the Fonts
	//---------------------------------------------------------------------------------------------------------
	
	SpriteFontManager::LoadDefaultResources();

	//---------------------------------------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------

	ImageManager::Load("FrogImg", TextureManager::Get("stitch"));
	ImageManager::Load("Heart", TextureManager::Get("Heart"));
	ImageManager::Load("Bullet", TextureManager::Get("Bullet"));
	ImageManager::Load("Site", TextureManager::Get("Site"));


	ImageManager::Load("Instructions", TextureManager::Get("Instructions"));
	ImageManager::Load("StartMessage", TextureManager::Get("StartMessage"));
	ImageManager::Load("FirstObjective", TextureManager::Get("FirstObjective"));
	ImageManager::Load("SecondObjective", TextureManager::Get("SecondObjective"));
	ImageManager::Load("landed", TextureManager::Get("landed"));

	ImageManager::Load("won", TextureManager::Get("won"));
	ImageManager::Load("lost", TextureManager::Get("lost"));
	ImageManager::Load("restart", TextureManager::Get("restart"));
	ImageManager::Load("objective", TextureManager::Get("objective"));

	//---------------------------------------------------------------------------------------------------------
	// Load the Terrain
	//---------------------------------------------------------------------------------------------------------

	TerrainManager::Load("MainTerrain", TextureManager::Get("test"), TextureManager::Get("Grass"), 36, 36, 1000, 60);
	TerrainManager::Load("FlatRoad", TextureManager::Get("test"), TextureManager::Get("RoadMap"), 1, 1, 3000, 1);

	//---------------------------------------------------------------------------------------------------------
	// Set Lights
	//---------------------------------------------------------------------------------------------------------




}