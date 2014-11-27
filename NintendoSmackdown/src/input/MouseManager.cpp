#include "MouseManager.h"
#include <iostream>

class Universe {

	public:
};

void MouseManager::event_update(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		mouse_down = true;
		start_mouse_pos = mouse_pos;
	}else if (e.type == SDL_MOUSEBUTTONUP) {
		mouse_down = false;
		mouse_released = true;
	}
}