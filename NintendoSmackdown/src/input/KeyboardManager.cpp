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
				break;
			case SDLK_LEFT:
				leftkeydown = true;
				break;
			case SDLK_UP:
				upkeydown = true;
				break;
			case SDLK_DOWN:
				downkeydown = true;
				break;
			case SDLK_d:
				rightkeydown = true;
				break;
			case SDLK_a:
				leftkeydown = true;
				break;
			case SDLK_w:
				upkeydown = true;
				break;
			case SDLK_s:
				downkeydown = true;
				break;
			case SDLK_z:
				akeydown = true;
				break;
			case SDLK_x:
				bkeydown = true;
				break;
		}
	}else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				rightkeydown = false;
				break;
			case SDLK_LEFT:
				leftkeydown = false;
				break;
			case SDLK_UP:
				upkeydown = false;
				break;
			case SDLK_DOWN:
				downkeydown = false;
				break;
			case SDLK_d:
				rightkeydown = false;
				break;
			case SDLK_a:
				leftkeydown = false;
				break;
			case SDLK_w:
				upkeydown = false;
				break;
			case SDLK_s:
				downkeydown = false;
				break;
			case SDLK_z:
				akeydown = false;
				break;
			case SDLK_x:
				bkeydown = false;
				break;
		}
	}
}