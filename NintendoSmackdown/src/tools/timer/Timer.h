#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <functional>

class Timer {

	public:
		Timer() { }

		std::function<void()> callback;
		int interval;
		clock_t start_time;
		bool repeat;
};

#endif