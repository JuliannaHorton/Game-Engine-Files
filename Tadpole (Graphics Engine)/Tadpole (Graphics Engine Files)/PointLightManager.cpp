#include "PointLightManager.h"
#include "ShaderTextureLight.h"
#include "ModelAttorney.h"
#include "ShaderColor.h"
#include "Model.h"
#include "Keyboard.h"
#include <iostream>

PointLightManager* PointLightManager::ptrInstance = nullptr;
std::map<int, PointLightManager::PointLight*> PointLightManager::lightMap;

PointLightManager::PointLightManager()
{
	//Sphere = new Model(Model::PreMadeModels::UnitSphere);
	//Arrow = new Model(Model::PreMadeModels::UnitPyramid);

	//shader = new ShaderColor();
	//mode = false;
}

PointLightManager::~PointLightManager()
{

	//delete Sphere;
	//delete Arrow;

	//delete shader;
}

void PointLightManager::privLoadLights()
{
	PointLight* flatShader = new PointLight();
	lightMap[1] = flatShader;

	PointLight* lightShader = new PointLight();
	lightMap[2] = lightShader;

	PointLight* colorShader = new PointLight();
	lightMap[3] = colorShader;
}

void PointLightManager::privMoveLight(ShaderBase* shader, int name, const Vect& newPos)
{

	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	PointLight* pt = it->second;
	pt->pos = newPos;

	if (name == 1)
		shader->SetPointLightParameters(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);
	else if (name == 2)
		shader->SetPointLightParameters2(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);
	else if (name == 3)
		shader->SetPointLightParameters3(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);

	ModelWorld = Matrix(SCALE, 2, 2, 2) * Matrix(TRANS, newPos);
}

void PointLightManager::privUpdateLight(ShaderBase* shader, int name, const Vect& newpos, const Vect& newAmb, const Vect& newDif, const Vect& newSp, const float newR, const Vect& newAtt)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	PointLight* pt = it->second;
	pt->pos = newpos;
	pt->amb = newAmb;
	pt->dif = newDif;
	pt->sp = newSp;
	pt->r = newR;
	pt->att = newAtt;

	//Remove these if statements eventually
	if (name == 1)
		shader->SetPointLightParameters(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);
	else if (name == 2)
		shader->SetPointLightParameters2(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);
	else if (name == 3)
		shader->SetPointLightParameters3(pt->pos, pt->r, pt->att, pt->amb, pt->dif, pt->sp);
}

void PointLightManager::privRemoveLight(int name)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	PointLight* pt = it->second;
	pt->shader->SetPointLightParameters(pt->pos, 0, Vect(0, 0, 0, 1), Vect(0, 0, 0, 1), Vect(0, 0, 0, 1), Vect(0, 0, 0, 1));
}

Vect PointLightManager::privGetPos(int name)
{
	auto it = lightMap.find(name);

	//Checks if the name already exists in the string 
	if (it == lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find light";
		OutputDebugString(message.c_str());

		assert(false && "Cannot find a selected name, check output for more details"); //Is it better to throw an error?
	}

	PointLight* pt = it->second;

	return pt->pos;
}

void PointLightManager::privTerminate()
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
void PointLightManager::findLight(int name)
{
	if (lightMap.find(name) != lightMap.end())
	{
		std::string message = "\n!!!!\nCannot find number\n!!!!\n\n";
		OutputDebugString(message.c_str());

		assert(false && "This number has already been used, check output for more details");
	}
}

void PointLightManager::privSendCamInfo(Matrix View, Matrix Proj, int lightMode)
{
	V = View;
	P = Proj;
	mode = lightMode;
}

void PointLightManager::privUpdate()
{

	/*if (mode == 1)
	{
		float lightSpeed = 1.5f;
		Vect Pos = PointLightManager::GetPos(1);

		if (Keyboard::GetKeyboardState(FROG_KEY::KEY_O))
		{
			Pos *= Matrix(TRANS, Vect(0, lightSpeed, 0));
			PointLightManager::MoveLight(1, Pos);
		}
		else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_P))
		{
			Pos *= Matrix(TRANS, Vect(0, -lightSpeed, 0));
			PointLightManager::MoveLight(1, Pos);
		}

		if (Keyboard::GetKeyboardState(FROG_KEY::KEY_I))
		{
			Pos *= Matrix(TRANS, Vect(0, 0, lightSpeed));
			PointLightManager::MoveLight(1, Pos);
		}
		else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_K))
		{
			Pos *= Matrix(TRANS, Vect(0, 0, -lightSpeed));
			PointLightManager::MoveLight(1, Pos);
		}

		if (Keyboard::GetKeyboardState(FROG_KEY::KEY_J))
		{
			Pos *= Matrix(TRANS, Vect(lightSpeed, 0, 0));
			PointLightManager::MoveLight(1, Pos);
		}
		else if (Keyboard::GetKeyboardState(FROG_KEY::KEY_L))
		{
			Pos *= Matrix(TRANS, Vect(-lightSpeed, 0, 0));
			PointLightManager::MoveLight(1, Pos);
		}
	}*/

}


void PointLightManager::privDraw()
{

	//shader->SetToContext();
	//shader->SendCamMatrices(V, P);

	//if (mode != 1)
	//{
	//	shader->SendWorldColor(ModelWorld, Colors::Yellow);
	//	ModelAttorney::SetToContext(Sphere);
	//	Sphere->Render();
	//}
	//else
	//{
	//	shader->SendWorldColor(ModelWorld, Colors::Green);
	//	ModelAttorney::SetToContext(Sphere);
	//	Sphere->Render();
	//}

}
