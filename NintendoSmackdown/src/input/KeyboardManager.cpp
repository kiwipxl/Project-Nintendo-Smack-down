#include "KeyboardManager.h"
#include <iostream>
#include "../GameLoop.h"

class Universe {

	public:
		static GameLoop* gameloop;
};

void KeyboardManager::eventupdate(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				break;
		}
	}else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_a:
				break;
		}
	}
}