#include "InputManager.h"
#include <iostream>
#include "../GameLoop.h"

class Universe {

	public:
		static GameLoop* game_loop;
};

void InputManager::initiate() {
	allkeys[0] = right_key;
	allkeys[1] = left_key;
	allkeys[2] = up_key;
	allkeys[3] = down_key;
	allkeys[4] = a_key;
	allkeys[5] = b_key;
	allkeys[6] = d_key;

	for (int n = 0; n < KEYS; ++n) {
		for (int i = 0; i < INPUTS; ++i) {
			allkeys[n][i] = new Key();
		}
	}

	//default p1 keyboard buttons
	right_key[0]->set_key(SDLK_RIGHT, KEYBOARD);
	left_key[0]->set_key(SDLK_LEFT, KEYBOARD);
	up_key[0]->set_key(SDLK_UP, KEYBOARD);
	down_key[0]->set_key(SDLK_DOWN, KEYBOARD);
	a_key[0]->set_key(SDLK_z, KEYBOARD);
	b_key[0]->set_key(SDLK_x, KEYBOARD);
	d_key[0]->set_key(SDLK_d, KEYBOARD);

	//default p2 joystick buttons
	right_key[1]->set_key(13, JOY_BUTTON);
	left_key[1]->set_key(15, JOY_BUTTON);
	up_key[1]->set_key(12, JOY_BUTTON);
	down_key[1]->set_key(14, JOY_BUTTON);
	a_key[1]->set_key(2, JOY_BUTTON);
	b_key[1]->set_key(1, JOY_BUTTON);

	//default p2 joystick axis
	/**
	right_key[1]->set_key(JOY_AXIS_RIGHT, JOY_AXIS);
	left_key[1]->set_key(JOY_AXIS_LEFT, JOY_AXIS);
	up_key[1]->set_key(JOY_AXIS_UP, JOY_AXIS);
	down_key[1]->set_key(JOY_AXIS_DOWN, JOY_AXIS);
	**/

	/**
	//default p2 joystick hat
	right_key[1]->set_key(JOY_HAT_RIGHT, JOY_HAT);
	left_key[1]->set_key(JOY_HAT_LEFT, JOY_HAT);
	up_key[1]->set_key(JOY_HAT_UP, JOY_HAT);
	down_key[1]->set_key(JOY_HAT_DOWN, JOY_HAT);
	**/

	refreshjoysticks();
}

void InputManager::refreshjoysticks() {
	joysticks.clear();
	cout << SDL_NumJoysticks() << " joysticks found\n";
	for (int n = 0; n < SDL_NumJoysticks(); ++n) {
		cout << (n + 1) << ". " << SDL_JoystickNameForIndex(n) << "\n";
		Joystick joystick;
		joystick.j = SDL_JoystickOpen(n);
		joystick.buttons = SDL_JoystickNumButtons(joystick.j);
		joystick.axes = SDL_JoystickNumAxes(joystick.j);
		joystick.hats = SDL_JoystickNumHats(joystick.j);
		joysticks.push_back(joystick);
		cout << (n + 1) << ". ";
		cout << joystick.buttons << " buttons, ";
		cout << joystick.axes << " axes, ";
		cout << joystick.hats << " hats\n";
	}
}

void InputManager::update() {
	for (int n = 0; n < KEYS; ++n) {
		for (int i = 0; i < INPUTS; ++i) {
			allkeys[n][i]->pressed = false;
		}
	}
}

void InputManager::event_update(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		set_keys_down(e.key.keysym.sym, KEYBOARD, true, true);
	}else if (e.type == SDL_KEYUP) {
		set_keys_down(e.key.keysym.sym, KEYBOARD, false);
	}else if (e.type == SDL_JOYBUTTONDOWN) {
		set_keys_down(e.jbutton.button, JOY_BUTTON, true);
	}else if (e.type == SDL_JOYBUTTONUP) {
		set_keys_down(e.jbutton.button, JOY_BUTTON, false);
	}else if (e.type == SDL_JOYAXISMOTION) {
		if (e.jaxis.axis == 0) {
			if (e.jaxis.value > 32000) {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, true);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, false);
			}else if (e.jaxis.value < -32000) {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, true);
			}else {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, false);
			}
		}else {
			if (e.jaxis.value > 32000) {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, true);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, false);
			}else if (e.jaxis.value < -32000) {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, true);
			}else {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, false);
			}
		}
	}else if (e.type == SDL_JOYHATMOTION) {
		int value = e.jhat.value;
		if (value == 0) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
			set_keys_down(JOY_HAT_DOWN, JOY_HAT, false);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
		}else if (value == SDL_HAT_UP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
		}else if (value == SDL_HAT_RIGHT) {
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, true);
		}else if (value == SDL_HAT_DOWN) {
			set_keys_down(JOY_HAT_DOWN, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
		}else if (value == SDL_HAT_LEFT) {
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, true);
		}else if (value == SDL_HAT_LEFTUP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, true);
		}else if (value == SDL_HAT_RIGHTUP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, true);
		}
	}
}

void InputManager::set_keys_down(int key, KeyType type, bool down, bool check_if_down) {
	for (int n = 0; n < KEYS; ++n) {
		for (int i = 0; i < INPUTS; ++i) {
			Key* inputkey = allkeys[n][i];
			if ((inputkey->type == type && key == inputkey->key) && (!check_if_down || !inputkey->down)) {
				inputkey->down = down;
				inputkey->pressed = down;
			}
		}
	}
}