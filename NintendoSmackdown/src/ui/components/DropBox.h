#ifndef DROPBOX_H
#define DROPBOX_H

#include <functional>
#include "Text.h"

class DropBox {

	public:
		DropBox(int c_id, int c_x, int c_y, std::string title, SDL_Colour colour) {
			id = c_id;
			y = c_y;
			dest_y = y;
			text = new Text(c_x, c_y, 20, colour, title, true, 160, CENTER);
		}

		int id;
		float y;
		float dest_y;
		Text* text;
		std::function<void()> press_function;

		void remove() { delete text; }
};

#endif