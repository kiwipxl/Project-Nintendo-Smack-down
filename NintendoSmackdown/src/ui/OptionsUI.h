#ifndef OPTIONS_UI_H
#define OPTIONS_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"

class OptionsUI : Universal {

	public:
		void create();
		void update();
		void remove();
		void resize_update(int w = 0, int h = 0);

	private:
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;
		DropdownBox* dropdown_box;
};

#endif