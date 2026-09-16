#ifndef _TimeManager
#define _TimeManager

class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;

private:

	static TimeManager* ptrInstance;

	TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() = default;

	static TimeManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new TimeManager();
		return *ptrInstance;
	};


	static void Delete(); //Called from Polliwog
	static void ProcessTime();

	//Used to for processing the time accurately  
	static float currentTime;
	static float frameTime;
	static float previousTime;

	static FreezeTime myFrzTime;

	//
	// Time Accessors
	//
	float privGetFrameTime();
	float privGetTime(); //Returns Total Time

public:

	/// <summary>
	/// \ingroup TIMEMANAGMENT
	/// \brief Returns the frametime
	/// </summary>
	/// <param name="name"></param>
	static float GetFrameTime() { return Instance().privGetFrameTime(); };
	/// <summary>
	/// \ingroup TIMEMANAGMENT
	/// \brief Returns the current time
	/// </summary>
	/// <param name="name"></param>
	static float GetTime() { return Instance().privGetTime(); };

};


#endif _TimeManager