#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <SDL.h>

class Joystick {

	public:
		Joystick() { }

		SDL_Joystick* j;
		int buttons;
		int axes;
};

#endif