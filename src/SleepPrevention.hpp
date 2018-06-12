
#pragma once

#include <windows.h>

class SleepPrevention {
private:
	const EXECUTION_STATE on = ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED;
	const EXECUTION_STATE off = ES_CONTINUOUS;

	EXECUTION_STATE state;

public:
	SleepPrevention();
	virtual ~SleepPrevention();

	bool getSleepPreventionState();
	void setSleepPreventionState(bool preventSleep);
	void cycleSleepPreventionState();
};

