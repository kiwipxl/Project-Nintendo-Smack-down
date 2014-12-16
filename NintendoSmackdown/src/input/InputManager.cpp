#include "InputManager.h"
#include <iostream>
#include <sstream>
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

	last_key = new Key();

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
	right_key[1]->set_key(JOY_AXIS_RIGHT, JOY_AXIS);
	left_key[1]->set_key(JOY_AXIS_LEFT, JOY_AXIS);
	up_key[1]->set_key(JOY_AXIS_UP, JOY_AXIS);
	down_key[1]->set_key(JOY_AXIS_DOWN, JOY_AXIS);

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
	last_key->pressed = false;
}

void InputManager::event_update(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		set_keys_down(e.key.keysym.sym, KEYBOARD, true, true);
		last_key->key = e.key.keysym.sym;
		last_key->pressed = true; last_key->down = true; last_key->type = KEYBOARD;
	}else if (e.type == SDL_KEYUP) {
		set_keys_down(e.key.keysym.sym, KEYBOARD, false);
		last_key->key = e.key.keysym.sym;
		last_key->down = false; last_key->type = KEYBOARD;
	}else if (e.type == SDL_JOYBUTTONDOWN) {
		set_keys_down(e.jbutton.button, JOY_BUTTON, true);
		last_key->key = e.jbutton.button;
		last_key->pressed = true; last_key->down = true; last_key->type = JOY_BUTTON;
	}else if (e.type == SDL_JOYBUTTONUP) {
		set_keys_down(e.jbutton.button, JOY_BUTTON, false);
		last_key->key = e.jbutton.button;
		last_key->down = false; last_key->type = JOY_BUTTON;
	}else if (e.type == SDL_JOYAXISMOTION) {
		if (e.jaxis.axis == 0) {
			if (e.jaxis.value > 32000) {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, true);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, false);
				last_key->key = JOY_AXIS_RIGHT;
				last_key->pressed = true; last_key->down = true; last_key->type = JOY_AXIS;
			}else if (e.jaxis.value < -32000) {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, true);
				last_key->key = JOY_AXIS_LEFT;
				last_key->pressed = true; last_key->down = true; last_key->type = JOY_AXIS;
			}else {
				set_keys_down(JOY_AXIS_RIGHT, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_LEFT, JOY_AXIS, false);
				last_key->down = false;
			}
		}else {
			if (e.jaxis.value > 32000) {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, true);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, false);
				last_key->key = JOY_AXIS_DOWN;
				last_key->pressed = true; last_key->down = true; last_key->type = JOY_AXIS;
			}else if (e.jaxis.value < -32000) {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, true);
				last_key->key = JOY_AXIS_UP;
				last_key->pressed = true; last_key->down = true; last_key->type = JOY_AXIS;
			}else {
				set_keys_down(JOY_AXIS_DOWN, JOY_AXIS, false);
				set_keys_down(JOY_AXIS_UP, JOY_AXIS, false);
				last_key->down = true;
			}
		}
	}else if (e.type == SDL_JOYHATMOTION) {
		int value = e.jhat.value;
		if (value == 0) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
			set_keys_down(JOY_HAT_DOWN, JOY_HAT, false);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
			last_key->down = true;
		}else if (value == SDL_HAT_UP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
			last_key->key = JOY_HAT_UP;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
		}else if (value == SDL_HAT_RIGHT) {
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, true);
			last_key->key = JOY_HAT_RIGHT;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
		}else if (value == SDL_HAT_DOWN) {
			set_keys_down(JOY_HAT_DOWN, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, false);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, false);
			last_key->key = JOY_HAT_DOWN;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
		}else if (value == SDL_HAT_LEFT) {
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, true);
			last_key->key = JOY_HAT_LEFT;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
		}else if (value == SDL_HAT_LEFTUP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_LEFT, JOY_HAT, true);
			last_key->key = JOY_HAT_UP;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
		}else if (value == SDL_HAT_RIGHTUP) {
			set_keys_down(JOY_HAT_UP, JOY_HAT, true);
			set_keys_down(JOY_HAT_RIGHT, JOY_HAT, true);
			last_key->key = JOY_HAT_UP;
			last_key->pressed = true; last_key->down = true; last_key->type = JOY_HAT;
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

std::string InputManager::get_name(Key* key) {
	std::string name;
	switch (key->type) {
		case JOY_BUTTON:
			name = "Button " + std::to_string(key->key);
			break;
		case JOY_AXIS:
			name = "Axis ";
			switch (key->key) {
				case JOY_AXIS_LEFT:
					name += "left";
					break;
				case JOY_AXIS_RIGHT:
					name += "right";
					break;
				case JOY_AXIS_UP:
					name += "up";
					break;
				case JOY_AXIS_DOWN:
					name += "down";
					break;
				default:
					name += std::to_string(key->key);
					break;
				}
			break;
		case JOY_HAT:
			name = "Hat ";
			switch (key->key) {
				case JOY_HAT_LEFT:
					name += "left";
					break;
				case JOY_HAT_RIGHT:
					name += "right";
					break;
				case JOY_HAT_UP:
					name += "up";
					break;
				case JOY_HAT_DOWN:
					name += "down";
					break;
				default:
					name += std::to_string(key->key);
					break;
				}
			break;
		default:
			name = SDL_GetKeyName(key->key);
			break;
	}
	return name;
}