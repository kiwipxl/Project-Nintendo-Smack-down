#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SDL.h>
#include <ctime>
#include <time.h>
#include "tools/Universal.h"

class GameLoop : Universal {

	public:
		GameLoop() {
			fps = 60;
			ms_per_frame = 0;
			quit = false;
		}

		float fps;

		void start();

	private:
		SDL_Event e;
		bool quit;
		std::clock_t start_time;
		std::clock_t start_second_time;
		float ms_per_frame;
		int frame_counter;
};

#endif