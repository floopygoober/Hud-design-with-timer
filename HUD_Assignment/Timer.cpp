#include "SDL.h"
#include "Timer.h"

// This is a class which keeps a simple clock using SDL_GetTicks()
// In this program it is used to get delta time in case it is needed for update methods
//
Timer::Timer() {
	prevTicks = 0;
	currTicks = 0;
}

Timer::~Timer() {}

void Timer::UpdateFrameTicks() {
	prevTicks = currTicks;
	currTicks = SDL_GetTicks();
}
//starts the clock
void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currTicks = SDL_GetTicks();
}
//finding your delta time in case it needs to be called outside the method
float Timer::GetDeltaTime() const {
	return (float(currTicks - prevTicks)) / 1000.0f;
}

unsigned int Timer::GetSleepTime(const unsigned int fps) const {
	unsigned int milliSecsPerFrame = 1000 / fps;
	if (milliSecsPerFrame == 0) {
		return 0;
	}

	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currTicks);
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}

	return sleepTime;
}