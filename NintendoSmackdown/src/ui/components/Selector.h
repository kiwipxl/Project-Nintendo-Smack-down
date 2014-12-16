#ifndef SELECTOR_H
#define SELECTOR_H

#include <SDL_rect.h>

class Selector {

	public:
		Selector() { }

		int input_id;
		SDL_Rect rect;
		bool selected = false;
};

#endif