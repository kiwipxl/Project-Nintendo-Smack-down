#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class MouseManager : Universal {

	public:
		MouseManager() {
			mouse_down = false;
			mouse_released = false;
		}

		Point2D mouse_pos;
		Point2D start_mouse_pos;
		bool mouse_down;
		bool mouse_released;

		void event_update(SDL_Event e);
};

#endif