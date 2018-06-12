
#include "SleepPrevention.hpp"

SleepPrevention::SleepPrevention()
	: state(off) {
}

SleepPrevention::~SleepPrevention() {
	this->setSleepPreventionState(false);
}

bool SleepPrevention::getSleepPreventionState() {
	return state == on;
}

void SleepPrevention::setSleepPreventionState(bool preventSleep) {
	this->state = preventSleep ? on : off;
	SetThreadExecutionState(this->state);
}

void SleepPrevention::cycleSleepPreventionState() {
	this->setSleepPreventionState(!this->getSleepPreventionState());
}
