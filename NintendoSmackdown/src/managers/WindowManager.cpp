#include "WindowManager.h"
#include <SDL_image.h>
#include <iostream>

void WindowManager::initiate() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialise SDL: " << SDL_GetError() << "\n";
	}else {
		window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "window could not be created: " << SDL_GetError() << "\n";
		}else {
			screensurface = SDL_GetWindowSurface(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				std::cout << "renderer could not be created: " << SDL_GetError() << "\n";
			}else {
				if (IMG_Init(IMG_INIT_PNG) == -1) {
					std::cout << "png could not be initialised: " << IMG_GetError() << "\n";
				}else {
					std::cout << "window initialised successfully\n";
				}
			}
		}
	}
}