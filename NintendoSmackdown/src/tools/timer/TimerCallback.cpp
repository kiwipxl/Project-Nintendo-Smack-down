#include "TimerCallback.h"
#include <iostream>
#include <ctime>
#include <algorithm>

void TimerCallback::set_timer(std::function<void()> callback, int interval, bool repeat) {
	Timer* timer = new Timer();
	timer->callback = callback;
	timer->interval = interval;
	timer->start_time = std::clock();
	timer->repeat = repeat;
	timers.push_back(timer);
}

void TimerCallback::update() {
	int timer_length = timers.size();
	for (int n = 0; n < timer_length; ++n) {
		if (timers[n] != nullptr && std::clock() - timers[n]->start_time > timers[n]->interval) {
			timers[n]->callback();
			if (!timers[n]->repeat) { timers[n] = nullptr; }
		}
	}
	timers.erase(std::remove(timers.begin(), timers.end(), nullptr), timers.end());
}