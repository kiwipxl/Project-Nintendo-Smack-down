#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"
#include "Joystick.h"
#include "Key.h"

#define JOY_AXIS_RIGHT -1
#define JOY_AXIS_LEFT -2
#define JOY_AXIS_UP -3
#define JOY_AXIS_DOWN -4
#define JOY_HAT_RIGHT -5
#define JOY_HAT_LEFT -6
#define JOY_HAT_UP -7
#define JOY_HAT_DOWN -8

class InputManager : Universal {

	public:
		InputManager() { }

		static const int INPUTS = 4;
		static const int KEYS = 7;

		Key* right_key[INPUTS];
		Key* left_key[INPUTS];
		Key* up_key[INPUTS];
		Key* down_key[INPUTS];

		Key* a_key[INPUTS];
		Key* b_key[INPUTS];

		Key* d_key[INPUTS];

		vector<Joystick> joysticks;
		Key*** allkeys = new Key**[KEYS];

		Key* last_key;

		void initiate();
		void event_update(SDL_Event e);
		void update();
		void refreshjoysticks();
		void set_keys_down(int key, KeyType type, bool down, bool check_if_down = false);
		std::string get_name(Key* key);
};

#endif