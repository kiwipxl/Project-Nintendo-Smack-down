#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class KeyboardManager : Universal {

	public:
		KeyboardManager() {

		}

		bool rightkeydown = false;
		bool leftkeydown = false;
		bool upkeydown = false;
		bool downkeydown = false;

		bool dkeydown = false;
		bool akeydown = false;
		bool wkeydown = false;
		bool skeydown = false;

		void eventupdate(SDL_Event e);
};

#endif