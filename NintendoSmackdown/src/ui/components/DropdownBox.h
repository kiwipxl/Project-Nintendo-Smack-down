#ifndef DROPDOWN_BOX_H
#define DROPDOWN_BOX_H

#include <SDL_rect.h>
#include <vector>
#include "../../tools/Universal.h"
#include "DropBox.h"

class DropdownBox : Universal {

	public:
		DropdownBox(int c_x, int c_y);
		~DropdownBox();

		void render();
		DropBox* add_box(std::string title, std::function<void()> press_function = nullptr, 
						 SDL_Colour colour = { 0, 0, 0 });
		void open();
		void close();
		void select(int index, bool call_press = false);

	private:
		int x;
		int y;
		SDL_Rect src_rect;
		SDL_Rect rect;
		vector<DropBox*> boxes;
		bool opened;
		DropBox* selected_box;
		DropBox* hover_box;
};

#endif