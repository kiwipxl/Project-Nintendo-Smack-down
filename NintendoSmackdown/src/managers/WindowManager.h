#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL.h>

class WindowManager {

	public:
		WindowManager() {
			screenwidth = 1080;
			screenheight = 768;

			centerx = screenwidth / 2;
			centery = screenheight / 2;
		}

		SDL_Window* window;
		SDL_Surface* screensurface;
		SDL_Renderer* renderer;

		int screenwidth;
		int screenheight;
		int centerx;
		int centery;

		void initiate();
		void resize(int w, int h);

	private:
		const char* WINDOW_TITLE = "Project Nintendo Smack-down";
};

#endif