#ifndef MENU_UI_H
#define MENU_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"

class MenuUI : Universal {

	public:
		void create();
		void update();
		void remove();
		void resize_update(int w = 0, int h = 0);

	private:
		float box_pos;
		int box_index;
		const int BOX_AMOUNT = 4;
		SDL_Rect box_rect;
		SDL_Rect box_src_rect;
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;
		DropdownBox* dropdown_box;
};

#endif