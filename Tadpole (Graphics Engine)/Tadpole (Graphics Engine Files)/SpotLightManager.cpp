#include "SpotLightManager.h"
#include "ShaderTextureLight.h"
#include "ModelAttorney.h"
#include "ShaderColor.h"
#include "Model.h"
#include "Keyboard.h"
#include <iostream>

SpotLightManager* SpotLightManager::ptrInstance = nullptr;
std::map<int, SpotLightManager::SpotLight*> SpotLightManager::lightMap;

SpotLightManager::SpotLightManager()
{
	//Sphere = new Model(Model::PreMadeModels::UnitSphere);
	//Arrow = new Model(Model::PreMadeModels::UnitPyramid);

	//shader = new ShaderColor();

	//mode = false;
}

SpotLightManager::~SpotLightManager()
{

	//delete Sphere;
	//delete Arrow;

	//delete shader;
}

void SpotLightManager::privLoadLights()
{
	SpotLight* flatShader = new SpotLight();
	lightMap[1] = flatShader;

	SpotLight* lightShader = new SpotLight();
	lightMap[2] = lightShader;

	SpotLight* colorShader = new SpotLight();
	lightMap[3] = colorShader;
}


void SpotLightManager::privMoveLight(ShaderBase* shader, int name, const Vect& newPos)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;
	pt->pos = newPos;

	if (name == 1)
		shader->SetSpotLightParameters(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 2)
		shader->SetSpotLightParameters2(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 3)
		shader->SetSpotLightParameters3(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);

}

void SpotLightManager::privTurnLight(ShaderBase* shader, int name, const Vect& newDir)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;
	pt->dir = newDir;

	if (name == 1)
		shader->SetSpotLightParameters(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 2)
		shader->SetSpotLightParameters2(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 3)
		shader->SetSpotLightParameters3(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);


	//ModelWorld = Matrix(SCALE, 2.5f, 4.5f, 2.5f) * Matrix(TRANS, pt->pos);

}

void SpotLightManager::privUpdateLight(ShaderBase* shader, int name, const Vect& newPos, const Vect& newDir, const Vect& newAmb, const Vect& newDif, const Vect& newSp, const float newR, const Vect& newAtt)
{

	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;
	pt->pos = newPos;
	pt->dir = newDir;
	pt->amb = newAmb;
	pt->dif = newDif;
	pt->sp = newSp;
	pt->r = newR;
	pt->att = newAtt;

	if (name == 1)
		shader->SetSpotLightParameters(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 2)
		shader->SetSpotLightParameters2(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);
	else if (name == 3)
		shader->SetSpotLightParameters3(pt->pos, pt->r, pt->att, pt->dir, 50, pt->amb, pt->dif, pt->sp);

}

void SpotLightManager::privRemoveLight(int name)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;
	pt->shader->SetSpotLightParameters(pt->pos, 0, Vect(0,0,0), Vect(0, 0, 0), 0, Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0));
}

Vect SpotLightManager::privGetPos(int name)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;

	return pt->pos;
}

Vect SpotLightManager::privGetDir(int name)
{
	auto it = lightMap.find(name);

	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	SpotLight* pt = it->second;

	return pt->dir;
}

void SpotLightManager::privTerminate()
{
	// Delete the pointer to the dynamically allocated object
	for (auto const& deleteMe : lightMap) {
		delete deleteMe.second;
	}
	lightMap.clear();

	//Deleting Instance for the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}

//Checks if the requested name already exists
void SpotLightManager::findLight(int name)
{
	if (lightMap.find(name) != lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find number\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This number has already been used, check output for more details");
	}
}

void SpotLightManager::privSendCamInfo(Matrix View, Matrix Proj, int lightMode)
{
	View, Proj, lightMode;
	//V = View;
	//P = Proj;
	//mode = lightMode;
}

void SpotLightManager::privDraw()
{

	/*shader->SetToContext();
	shader->SendCamMatrices(V, P);

	if (mode != 2)
	{  
		shader->SendWorldColor(ModelWorld, Colors::Yellow);
		ModelAttorney::SetToContext(Arrow);
		Arrow->Render();
	}
	else
	{
		shader->SendWorldColor(ModelWorld, Colors::Green);
		ModelAttorney::SetToContext(Arrow);
		Arrow->Render();
	}*/

}

void SpotLightManager::privUpdate()
{
	//if (mode == 2)
	//{
	//	float lightSpeed = 1.5f;
	//	Vect Pos = SpotLightManager::GetPos(1);
	//	Vect Dir = SpotLightManager::GetDir(1);
	//
	//	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_O))
	//	{
	//		Pos *= Matrix(TRANS, Vect(0, lightSpeed, 0));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_P))
	//	{
	//		Pos *= Matrix(TRANS, Vect(0, -lightSpeed, 0));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//
	//	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_I))
	//	{
	//		Pos *= Matrix(TRANS, Vect(0, 0, lightSpeed));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_K))
	//	{
	//		Pos *= Matrix(TRANS, Vect(0, 0, -lightSpeed));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//
	//	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_J))
	//	{
	//		Pos *= Matrix(TRANS, Vect(lightSpeed, 0, 0));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_L))
	//	{
	//		Pos *= Matrix(TRANS, Vect(-lightSpeed, 0, 0));
	//		SpotLightManager::MoveLight(1, Pos);
	//	}
	//
	//	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_T))
	//	{
	//		Dir *= Matrix(ROT_X, 0.05f);
	//		SpotLightManager::TurnLight(1, Dir);
	//	}
	//	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_G))
	//	{
	//		Dir *= Matrix(ROT_X, -0.05f);
	//		SpotLightManager::TurnLight(1, Dir);
	//	}
	//
	//	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_F))
	//	{
	//		Dir *= Matrix(ROT_Y, 0.05f);
	//		SpotLightManager::TurnLight(1, Dir);
	//	}
	//	else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_H))
	//	{
	//		Dir *= Matrix(ROT_Y, -0.05f);
	//		SpotLightManager::TurnLight(1, Dir);
	//	}
	//}

}
