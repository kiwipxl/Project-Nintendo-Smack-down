#ifndef MENU_UI_H
#define MENU_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"

class MenuUI : Universal {

	public:
		void create();
		void update();
		void remove();
		void resize_update(int w = 0, int h = 0);

	private:
		float box_pos;
		int box_index;
		float box_dest_x;
		const int BOX_AMOUNT = 4;
		SDL_Rect box_rect;
		SDL_Rect box_src_rect;
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;
};

#endif