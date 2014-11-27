#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"
#include "Joystick.h"
#include "Key.h"

enum ExtraKeyConstants {
	JOY_AXIS_RIGHT = -1, 
	JOY_AXIS_LEFT = -2, 
	JOY_AXIS_UP = -3, 
	JOY_AXIS_DOWN = -4
};

class InputManager : Universal {

	public:
		InputManager() { }

		static const int KEYS = 4;

		Key right_key[KEYS] = { };
		Key left_key[KEYS] = { };
		Key up_key[KEYS] = { };
		Key down_key[KEYS] = { };
		
		Key a_key[KEYS] = { };
		Key b_key[KEYS] = { };

		vector<Joystick> joysticks;

		void initiate();
		void event_update(SDL_Event e);
		void refreshjoysticks();
		void set_keys_down(int key, KeyType type, bool down);
};

#endif