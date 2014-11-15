#include "MouseManager.h"
#include <iostream>

class Universe {

	public:
};

void MouseManager::eventupdate(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		mousedown = true;
		startmousepos = mousepos;
	}else if (e.type == SDL_MOUSEBUTTONUP) {
		mousedown = false;
		mousereleased = true;
	}
}