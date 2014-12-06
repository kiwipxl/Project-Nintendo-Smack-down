#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL.h>
#include <glew.h>
#include "../tools/Universal.h"

class WindowManager : Universal {

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

		SDL_GLContext context;

		/**
		creates and initialises the window and renderer
		**/
		void initiate();
		/**
		updates the screen width and height to a new value and updates the state
		**/
		void resize(int w, int h);
		/**
		updates the screen width and height to the current window resolution and updates the state
		**/
		void update_resize();

	private:
		const char* WINDOW_TITLE = "Project Nintendo Smack-down";
};

#endif