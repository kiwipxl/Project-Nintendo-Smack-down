#ifndef TIMER_CALLBACK_H
#define TIMER_CALLBACK_H

#include <vector>
#include "Timer.h"

class TimerCallback {

	public:
		TimerCallback() { }

		Timer* set_timer(std::function<void()> callback, int interval, bool repeat = false);
		void update();
		void remove_timer(Timer* &timer);

	private:
		std::vector<Timer*> timers;
};

#endif