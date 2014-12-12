#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_rect.h>
#include <functional>
#include "../../tools/Universal.h"
#include "Text.h"

class Button : Universal {

	public:
		Button(int c_x, int c_y, std::string title, std::function<void()> press = nullptr,
			int width = 192, int height = 64, int font_size = 25, SDL_Colour colour = { 0, 0, 0 });
		~Button();

		int origin_x;
		int origin_y;
		bool removed;

		void render();
		void set_pos(int c_x, int c_y);
		int get_x() { return x; }
		int get_y() { return y; }

	private:
		int x;
		int y;
		SDL_Rect src_rect;
		SDL_Rect rect;
		Text* text;
		std::function<void()> press_function;
};

#endif