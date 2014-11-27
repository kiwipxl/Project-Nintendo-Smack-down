#include "KeyboardManager.h"
#include <iostream>
#include "../GameLoop.h"

class Universe {

	public:
		static GameLoop* game_loop;
};

void KeyboardManager::event_update(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				right_key_down = true;
				break;
			case SDLK_LEFT:
				left_key_down = true;
				break;
			case SDLK_UP:
				up_key_down = true;
				break;
			case SDLK_DOWN:
				down_key_down = true;
				break;
			case SDLK_d:
				right_key_down = true;
				break;
			case SDLK_a:
				left_key_down = true;
				break;
			case SDLK_w:
				up_key_down = true;
				break;
			case SDLK_s:
				down_key_down = true;
				break;
			case SDLK_z:
				a_key_down = true;
				break;
			case SDLK_x:
				b_key_down = true;
				break;
		}
	}else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				right_key_down = false;
				break;
			case SDLK_LEFT:
				left_key_down = false;
				break;
			case SDLK_UP:
				up_key_down = false;
				break;
			case SDLK_DOWN:
				down_key_down = false;
				break;
			case SDLK_d:
				right_key_down = false;
				break;
			case SDLK_a:
				left_key_down = false;
				break;
			case SDLK_w:
				up_key_down = false;
				break;
			case SDLK_s:
				down_key_down = false;
				break;
			case SDLK_z:
				a_key_down = false;
				break;
			case SDLK_x:
				b_key_down = false;
				break;
		}
	}
}