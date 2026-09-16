// FreezeTime
// Andre Berthiaume, Jan 2022

#ifndef _FreezeTime
#define _FreezeTime

#include "../Keyboard.h"

class FreezeTime
{
private:
	static const FROG_KEY FREEZE_KEY = FROG_KEY::KEY_F;
	static const FROG_KEY SINGLE_FRAME_KEY = FROG_KEY::KEY_F9;

	static const float DEAD_TIME_THRESHOLD;
	const float DEFAULT_FRAME_TIME;  // Not static since automatically adjusted to monitor's refesh rate

	float totalFrozenTime;
	bool freeze_mode_active;

	bool HackedKeyRelease(FROG_KEY k);
	void TestForFreezeKeys();

	DWORD FreezeTime::GetRefreshRate();

public:
	FreezeTime();
	~FreezeTime() {};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	/// <summary>
	/// \ingroup TIMEMANAGMENT
	/// \brief Returns the current in-game time
	/// </summary>
	/// <param name="name"></param>
	float ComputeGameTime(float prev_time);
};

#endif _FreezeTime