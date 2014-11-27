#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL.h>

class WindowManager {

	public:
		WindowManager() {
			screen_width = 1080;
			screen_height = 768;

			center_x = screen_width / 2;
			center_y = screen_height / 2;
		}

		SDL_Window* window;
		SDL_Surface* screen_surface;
		SDL_Renderer* renderer;

		int screen_width;
		int screen_height;
		int center_x;
		int center_y;

		void initiate();
		void resize(int w, int h);

	private:
		const char* WINDOW_TITLE = "Project Nintendo Smack-down";
};

#endif