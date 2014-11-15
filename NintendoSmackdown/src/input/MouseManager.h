#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class MouseManager : Universal {

	public:
		MouseManager() {
			mousedown = false;
			mousereleased = false;
		}

		Point2D mousepos;
		Point2D startmousepos;
		bool mousedown;
		bool mousereleased;

		void eventupdate(SDL_Event e);
};

#endif