#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <SDL_rect.h>
#include <vector>
#include "../../tools/Universal.h"
#include "Text.h"
#include "Button.h"

class MessageBox : Universal {

	public:
		MessageBox(int c_x, int c_y, std::string title, std::string message, int message_font_size = 20);
		~MessageBox();

		SDL_Rect rect;
		bool removed;

		void render();
		void add_button(Button* button);

		void set_pos(int c_x, int c_y);

		int get_width() { return rect.w; }
		int get_height() { return rect.h; }

		void resize_update(int w = 0, int h = 0);

	private:
		int x;
		int y;
		SDL_Rect src_rect;
		SDL_Rect bg_src_rect;
		SDL_Rect bg_rect;
		Text* title_text;
		Text* message_text;
		vector<Button*> buttons;
};

#endif