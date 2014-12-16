#include "WindowManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "StateManager.h"

class Universe {

	public:
		static StateManager* state;
};

void WindowManager::initiate() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "could not initialise SDL: " << SDL_GetError() << "\n";
	}else {
		window_flags = SDL_WINDOW_SHOWN;
		window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								  screen_width, screen_height, window_flags | SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "window could not be created: " << SDL_GetError() << "\n";
		}else {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			context = SDL_GL_CreateContext(window);
			if (context == NULL) {
				std::cout << "context could not be created: " << SDL_GetError() << "\n";
			}else {
				glViewport(0, 0, screen_width, screen_height);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, screen_width, screen_height, 0, 1, -1);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				if (glGetError() != GL_NO_ERROR) {
					std::cout << "an error occurred while setting up matrix mode: " << glGetError() << "\n";
				}
				glClearColor(1, 1, 1, 1);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);

				if (glewInit() == GLEW_OK) {
					std::cout << "glew initiated\n";
				}else {
					std::cout << "glew initialisation failed\n";
				}

				std::cout << "opengl initiated (version: " << glGetString(GL_VERSION) << ")\n";
			}
			if (IMG_Init(IMG_INIT_PNG) == -1) {
				std::cout << "png could not be initialised: " << IMG_GetError() << "\n";
			}else {
				std::cout << "window initialised successfully\n";
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				std::cout << "initiated mixer successfully\n";
			}else {
				std::cout << "mixer could not be initiated. error: " << Mix_GetError() << "\n";
			}

			SDL_DisplayMode display;
			std::cout << SDL_GetNumVideoDisplays() << " available displays found\n";
			for (int n = 0; n < SDL_GetNumVideoDisplays(); ++n) {
				SDL_GetCurrentDisplayMode(n, &display);
				SDL_Rect bounds;
				bounds.w = display.w;
				bounds.h = display.h;
				window_bounds.push_back(bounds);
				std::cout << (n + 1) << ". " << SDL_GetDisplayName(n);
				std::cout << ", screen res: (" << bounds.w << "x" << bounds.h << ")\n";
			}
		}
	}
}

void WindowManager::resize(int w, int h) {
	screen_width = w;
	screen_height = h;
	center_x = w / 2;
	center_y = h / 2;

	SDL_SetWindowSize(window, w, h);

	glViewport(0, 0, screen_width, screen_height);
	glViewport(0, 0, screen_width, screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_width, screen_height, 0, 1, -1);

	std::cout << "resized window: " << w << "x" << h << "\n";

	universe->state->resize_current_state();
}

void WindowManager::update_resize() {
	SDL_GetWindowSize(window, &screen_width, &screen_height);

	center_x = screen_width / 2;
	center_y = screen_height / 2;

	glViewport(0, 0, screen_width, screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_width, screen_height, 0, 1, -1);

	std::cout << "resized window: " << screen_width << "x" << screen_height << "\n";

	universe->state->resize_current_state();
}

void WindowManager::set_window_flags(SDL_WindowFlags flags) {
	window_flags = flags;
	SDL_SetWindowFullscreen(window, false);
	SDL_SetWindowBordered(window, SDL_TRUE);

	switch (flags) {
		case SDL_WINDOW_SHOWN:
			SDL_SetWindowPosition(window, 32, 32);
			break;
		case SDL_WINDOW_BORDERLESS:
			SDL_SetWindowBordered(window, SDL_FALSE);
			SDL_SetWindowSize(window, window_bounds[0].w, window_bounds[0].h);
			screen_width = window_bounds[0].w;
			screen_height = window_bounds[0].h;
			SDL_SetWindowPosition(window, 0, 0);
			break;
		case SDL_WINDOW_FULLSCREEN_DESKTOP:
			SDL_SetWindowFullscreen(window, true);
			SDL_SetWindowBordered(window, SDL_TRUE);
			SDL_SetWindowPosition(window, 0, 0);
			break;
		case SDL_WINDOW_RESIZABLE:
			SDL_SetWindowPosition(window, 32, 32);
			break;
	}
}