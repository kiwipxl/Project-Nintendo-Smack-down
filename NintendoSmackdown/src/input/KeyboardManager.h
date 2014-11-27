#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class KeyboardManager : Universal {

	public:
		KeyboardManager() {

		}

		bool right_key_down = false;
		bool left_key_down = false;
		bool up_key_down = false;
		bool down_key_down = false;

		bool a_key_down = false;
		bool b_key_down = false;

		void event_update(SDL_Event e);
};

#endif