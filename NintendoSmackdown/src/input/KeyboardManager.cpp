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
			case SDLK_RIGHT:
				rightkeydown = true;
				dkeydown = true;
				break;
			case SDLK_LEFT:
				leftkeydown = true;
				akeydown = true;
				break;
			case SDLK_UP:
				upkeydown = true;
				wkeydown = true;
				break;
			case SDLK_DOWN:
				downkeydown = true;
				skeydown = true;
				break;
		}
	}else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				rightkeydown = false;
				dkeydown = false;
				break;
			case SDLK_LEFT:
				leftkeydown = false;
				akeydown = false;
				break;
			case SDLK_UP:
				upkeydown = false;
				wkeydown = false;
				break;
			case SDLK_DOWN:
				downkeydown = false;
				skeydown = false;
				break;
		}
	}
}