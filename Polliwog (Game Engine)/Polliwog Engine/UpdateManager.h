#pragma once

#ifndef _UpdateManager
#define _UpdateManager

#include <list>

class Updatable;

class UpdateManager
{
private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;

public:
	UpdateManager() = default;
	UpdateManager(const UpdateManager&) = delete;
	UpdateManager& operator=(const UpdateManager&) = delete;
	~UpdateManager() = default;

	using StorageListRef = StorageList::iterator;

	void Register(Updatable* drawing, StorageListRef& ref);
	void Deregister(const StorageListRef&);
	void ProcessElements();

};

#endif _UpdateManager
