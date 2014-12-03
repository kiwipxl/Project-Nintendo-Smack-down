#ifndef TIMER_CALLBACK_H
#define TIMER_CALLBACK_H

#include <vector>
#include "Timer.h"

class TimerCallback {

	public:
		TimerCallback() { }

		void set_timer(std::function<void()> callback, int interval);
		void update();

	private:
		std::vector<Timer*> timers;
};

#endif