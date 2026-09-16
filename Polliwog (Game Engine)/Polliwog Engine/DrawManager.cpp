#include "DrawManager.h"
#include "DrawAttorney.h"

void DrawManager::Register(Drawable* draw, StorageListRef& ref)
{
	ref = storageList.insert(storageList.end(), draw);

	DrawAttorney::GameLoop::SetDelete(draw, ref);

}

void DrawManager::Deregister(const StorageListRef& ref)
{
	storageList.erase(ref);
}

void DrawManager::ProcessElements()
{
	for (auto& drawing : storageList)
	{
		DrawAttorney::GameLoop::Draw(drawing);
	}

	for (auto& drawing : storageList) //2D objects must be called after 3D ones
	{
		DrawAttorney::GameLoop::Draw2D(drawing);
	}


}