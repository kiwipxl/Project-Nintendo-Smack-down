#include "InputManager.h"
#include <iostream>
#include "../GameLoop.h"

class Universe {

	public:
		static GameLoop* game_loop;
};

void InputManager::initiate() {
	right_key[0].set_key(SDLK_RIGHT, KEYBOARD);
	left_key[0].set_key(SDLK_LEFT, KEYBOARD);
	up_key[0].set_key(SDLK_UP, KEYBOARD);
	down_key[0].set_key(SDLK_DOWN, KEYBOARD);
	a_key[0].set_key(SDLK_z, KEYBOARD);
	b_key[0].set_key(SDLK_x, KEYBOARD);

	right_key[1].set_key(13, JOY_BUTTON);
	left_key[1].set_key(15, JOY_BUTTON);
	up_key[1].set_key(12, JOY_BUTTON);
	down_key[1].set_key(14, JOY_BUTTON);
	a_key[1].set_key(2, JOY_BUTTON);
	b_key[1].set_key(1, JOY_BUTTON);

	right_key[1].set_key(JOY_AXIS_RIGHT, JOY_AXIS);
	left_key[1].set_key(JOY_AXIS_LEFT, JOY_AXIS);
	up_key[1].set_key(JOY_AXIS_UP, JOY_AXIS);
	down_key[1].set_key(JOY_AXIS_DOWN, JOY_AXIS);

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
		joysticks.push_back(joystick);
		cout << (n + 1) << ". ";
		cout << joystick.buttons << " buttons, ";
		cout << joystick.axes << " axes\n";
	}
}

void InputManager::event_update(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		set_keys_down(e.key.keysym.sym, KEYBOARD, true);
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
	}
}

void InputManager::set_keys_down(int key, KeyType type, bool down) {
	for (int n = 0; n < KEYS; ++n) {
		if (right_key[n].type == type && key == right_key[n].key) {
			right_key[n].down = down;
		}else if (left_key[n].type == type && key == left_key[n].key) {
			left_key[n].down = down;
		}else if (up_key[n].type == type && key == up_key[n].key) {
			up_key[n].down = down;
		}else if (down_key[n].type == type && key == down_key[n].key) {
			down_key[n].down = down;
		}else if (a_key[n].type == type && key == a_key[n].key) {
			a_key[n].down = down;
		}else if (b_key[n].type == type && key == b_key[n].key) {
			b_key[n].down = down;
		}
	}
}