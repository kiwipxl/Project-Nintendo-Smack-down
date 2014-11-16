#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SDL.h>
#include <ctime>
#include "tools/Universal.h"

class GameLoop : Universal {

	public:
		GameLoop() {
			fps = 60;
			msperframe = 0;
			quit = false;
		}

		float fps;

		void start();

	private:
		SDL_Event e;
		bool quit;
		std::clock_t starttime;
		std::clock_t startsecondtime;
		float msperframe;
		int framecounter;
};

#endif